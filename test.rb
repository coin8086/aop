#!/usr/bin/env ruby

def test(basename, debug = false)
  src = basename + '.cpp'
  input = basename + '.input'
  expect = basename + '.expect'
  bin = "/tmp/#{basename}"
  output = "/tmp/#{basename}.output"

  [src, input, expect].each do |f|
    raise "File `#{f}' doesn't exist!" if !File.exist?(f)
  end

  if debug
    raise if !system("g++ #{src} -o #{bin} -g")
  elsif !File.exist?(bin) || (File.mtime(bin) < File.mtime(src))
    raise if !system("g++ #{src} -o #{bin} -O2")
  end

  while !File.exist?(bin)
    sleep(1)
  end

  if debug
    system("gdb #{bin}")
  else
    system "time -p #{bin} < #{input} > #{output}"
    while !File.exist?(output)
      sleep(1)
    end
    ok = system("diff #{expect} #{output}")
    puts ok ? "OK!" : "Failed!"
  end
end

if __FILE__ == $0
  fail "Specify a source file to test" if !ARGV[0]

  basename = File.basename(ARGV[0], '.cpp')
  debug = ['-d', '--debug'].include?(ARGV[1])
  test(basename, debug)
end

