#!/bin/sh
# Public-release sanitization, preserving all bytes outside marked blocks.
set -eu
find "$@" -type f -exec perl -0777 -i -e '
  my @stack; my $out = "";
  for my $line (split /(?<=\n)/, $_) {
    if ($line =~ /start-sanitize-([\w-]+)/) { push @stack, $1; }
    elsif ($line =~ /end-sanitize-([\w-]+)/) {
      die "mismatched sanitize block in $ARGV\n" unless @stack && pop(@stack) eq $1;
    } elsif (!@stack) { $out .= $line; }
  }
  die "unclosed sanitize block in $ARGV\n" if @stack;
  $_ = $out;
' {} +
