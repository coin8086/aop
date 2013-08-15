#!/usr/bin/env ruby

require_relative 'test_helper'

def count_one(n)
  c = 0
  while n != 0
    if n % 10 == 1
      c += 1
    end
    n /= 10
  end
  c
end

a = []
c = 0
(1..10000).each do |i|
  c += count_one(i)
  a << [i, c]
end

b = []
(10001..1000000).each do |i|
  c += count_one(i)
  b << [i, c]
end

(1..10000).each do |i|
  a << b[rand(1000000 - 10000)]
end
b = nil

test_file = File.expand_path(__FILE__)
test(test_file) do |input, output|
  input = File.open(input, 'wb')
  output = File.open(output, 'wb')
  a.each do |e|
    input.puts e[0]
    output.puts e[1]
  end
  input.close
  output.close
end
