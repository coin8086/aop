def try_ops(x, y, swap = false)
  return if yield(x + y, '+')
  return if yield(x - y, '-')
  return if swap && yield(y - x, '-', true)
  return if yield(1.0 * x * y, '*')
  return if y != 0 && yield(1.0 * x / y, '/')
  swap && x != 0 && yield(1.0 * y / x, '/', true)
end

# There're two kinds of expressions:
# 1) t1 = n1 op n2
#    t2 = n3 op n4
#    t3 = t1 op t2
# 2) t1 = n1 op n2
#    t2 = t1 op n3 | n3 op t1
#    t3 = t2 op n4 | n4 op t2
# There's no need for the first kind to have "n4 op n3" or "t2 op t1" because
# if all permutations of input array is enumerated, then "n4 op n3" or "t2 op t1"
# must be included. But this is not true for the second kind. Think about that
# in a binary tree for an expression.
def solve(a)
  raise ArgumentError if a.size != 4

  a.permutation do |p|
    try_ops(p[0], p[1]) do |r, op1|
      try_ops(p[2], p[3]) do |r2, op2|
        try_ops(r, r2) do |r3, op3|
          if (r3 - 24).abs < 0.000001 # Required for comparing float with 0
            return "(#{p[0]} #{op1} #{p[1]}) #{op3} (#{p[2]} #{op2} #{p[3]})"
          end
        end
      end

      try_ops(r, p[2], true) do |r2, op2, swapped2|
        try_ops(r2, p[3], true) do |r3, op3, swapped3|
          if (r3 - 24).abs < 0.000001
            s = "(#{p[0]} #{op1} #{p[1]})"
            s = swapped2 ? "(#{p[2]} #{op2} #{s})" : "(#{s} #{op2} #{p[2]})"
            s = swapped3 ? "#{p[3]} #{op3} #{s}" : "#{s} #{op3} #{p[3]}"
            return s
          end
        end
      end
    end
  end

  nil
end

if __FILE__ == $0
  $stdin.each_line do |line|
    a = line.split.map {|e| e.to_i }
    r = solve(a)
    if r
      puts r
    else
      puts "Impossible."
    end
  end
end
