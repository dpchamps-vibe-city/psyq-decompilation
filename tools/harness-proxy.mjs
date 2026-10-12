#!/usr/bin/env node
// Keep implementation and dependencies in the Pi-installed harness, not this repo.
import { spawn } from "node:child_process";
import { existsSync, readFileSync, realpathSync } from "node:fs";
import { createRequire } from "node:module";
import { constants } from "node:os";
import { dirname, isAbsolute, resolve } from "node:path";
import { fileURLToPath, pathToFileURL } from "node:url";

const projectRoot = resolve(dirname(fileURLToPath(import.meta.url)), "..");

function installedHarness() {
  const settingsPath = resolve(projectRoot, ".pi/settings.json");
  const settings = JSON.parse(readFileSync(settingsPath, "utf8"));
  const candidates = new Set();
  for (const entry of settings.packages ?? []) {
    const source = typeof entry === "string" ? entry : entry?.source;
    if (typeof source !== "string" || (!isAbsolute(source) && !source.startsWith("."))) continue;
    // Pi resolves local package entries relative to the settings directory.
    const root = resolve(dirname(settingsPath), source);
    const manifest = resolve(root, "package.json");
    if (!existsSync(manifest)) continue;
    if (JSON.parse(readFileSync(manifest, "utf8")).name === "psx-decompilation-harness") {
      candidates.add(realpathSync(root));
    }
  }
  if (candidates.size !== 1) {
    throw new Error("Expected one local psx-decompilation-harness package in .pi/settings.json.");
  }
  return [...candidates][0];
}

try {
  const [entry, ...args] = process.argv.slice(2);
  if (!entry) throw new Error("Use npm run to list the project commands.");
  if (args.includes("--project")) throw new Error("These proxy commands always target this repository.");
  const harness = installedHarness();
  const host = resolve(harness, "tools/lib/scriptHost.ts");
  const loader = createRequire(resolve(harness, "package.json")).resolve("tsx");
  const child = spawn(process.execPath, [
    "--import", pathToFileURL(loader).href, host, entry, "--project", projectRoot, ...args,
  ], { cwd: projectRoot, stdio: "inherit" });

  const handlers = new Map();
  for (const signal of ["SIGINT", "SIGTERM"]) {
    const handler = () => child.kill(signal);
    handlers.set(signal, handler);
    process.on(signal, handler);
  }
  function detachHandlers() {
    for (const [signal, handler] of handlers) process.removeListener(signal, handler);
  }
  child.on("error", error => {
    detachHandlers();
    console.error(`PSX command failed: ${error.message}`);
    process.exitCode = 1;
  });
  child.on("exit", (code, signal) => {
    detachHandlers();
    process.exitCode = code ?? (signal ? 128 + (constants.signals[signal] ?? 0) : 1);
  });
} catch (error) {
  console.error(`PSX command failed: ${error.message}`);
  process.exitCode = 1;
}
