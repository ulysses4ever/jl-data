# code for specifying a parametrizable grammar, along with processing and
# computing the cost of a non-terminal and productions

type Production
  cost::Int64
  p::Array{Any}
end

function production(x...)
  Production(typemax(Int64), [x...])
end

type Rule
  non_term :: Symbol
  cost::Int64
  productions :: Array{Production}
end

function rule(nt::Symbol, productions::Array{Production})
  Rule(nt, typemax(Int64), productions)
end

type Grammar
  rules::Array{Rule}
end

rule1 = rule(:E, [production(:var, :V),
                  production(:const),
                  production(:call, :F1, :E),
                  production(:call, :F2, :E, :E)
                  ])

rule2 = rule(:F2, [production(+),
                   production(-),
                   production(*)
                   ])

rule3 = rule(:F1, [production(x->(-x)),
                   production(x->1-x)
                   ])

rule4 = rule(:V, [production(:x1),
                  production(:x2),
                  production(:x3)
                  ])

grammar1 = Grammar([rule1, rule2, rule3, rule4])

# find the rule with the non_terminal on the lefthandside
find_rule(non_term::Symbol, g::Grammar) = filter(rul->(rul.non_term == non_term), g.rules)[1]

function param_cost(p::Production, g::Grammar, seen::Array{Symbol})
  syms = p.p
  op = syms[1]
  p.cost = 0
  if op == :var
    p.cost = 1
  end
  if op == :const
    p.cost = 1
  end
  if op == :call
    rest = syms[2:end]
    p.cost = sum([param_cost(non_term, g, seen) for non_term in rest])
  end
  p.cost
end

function param_cost(non_term::Symbol, g::Grammar, seen::Array{Symbol})
  rule = find_rule(non_term, g)
  if rule.cost != typemax(Int64)
    rule.cost
  else
    function hasnt_seen(p::Production)
      syms = p.p
      for sym in syms
        if sym in seen
          return false
        end
      end
      true
    end
    valid_prods = filter(p->hasnt_seen(p), rule.productions)
    assert(length(valid_prods) > 0)
    costs = [param_cost(p, g, [seen, non_term]) for p in valid_prods]
    ret = 1 + min(costs...)
    rule.cost = ret
    ret
  end
end

function compute_cost(g::Grammar)
  # first compute the cost for all the non-terminals
  for rule in g.rules
    non_term = rule.non_term
    param_cost(non_term, g, Symbol[])
  end
  # then compute the cost for all the productions
  for rule in g.rules
    for prod in rule.productions
      param_cost(prod, g, Symbol[])
    end
    rule.productions = sort(rule.productions, by=prod->prod.cost)
  end
end


# code for generating an expression from a parametrizable grammar

function idx_dist_from_param(θ::Float64, n::Int64)
  truemod(a, m) = (if a % m >= 0
                     a % m
                   else
                     m + (a % m)
                   end
                   )
  [(min(truemod(θ-i, n),truemod(i-θ, n)),i) for i in 0:n-1]
end

# given a parameter θ, a choice of n items, and β for spread
# gives a normalized weight of these n items
# the weight favors the item which θ is most close to, under modulo arithmentic
function idx_weight_from_beta(θ::Float64, n::Int64, β::Float64)
  re_weight(dist::Float64, β::Float64) = (2 ^ (-dist * β))
  idx_dist = idx_dist_from_param(θ, n)
  un_normalized_weights = [(re_weight(x[1], β), x[2]) for x in idx_dist]
  weight_total = sum([x[1] for x in un_normalized_weights])
  [(x[1] / weight_total, x[2]) for x in un_normalized_weights]
end

using Gadfly
plot(x->idx_weight_from_beta(2.51, 3, x)[3][1], 0.0, 50.0)

# generate an expression from a non-terminal with spread \beta  and parameters11
function expgen(nt::Symbol, g::Grammar, θs::Array{Float64}, β::Float64)
end

idx_weight_from_beta(2.7, 3, 1.1)

idx_dist_from_param(2.7, 3)
split_idx_weight(0.7, 3)
split_idx_weight(1.2, 3)
split_idx_weight(3.2, 3)

compute_cost(grammar1)
println (grammar1)



param_cost(:V, grammar1, Symbol[])
param_cost(:F1, grammar1, Symbol[])
param_cost(:E, grammar1, Symbol[])

x = 3
expr = parse("x + x")
typeof(expr)
dump(expr)
eval(expr)
expr.head

apply
:var
var([1,2,3,4,1,2,3])
prod1 = Production([:call, :x, :y])
prod2 = Production([:var])
rule1 = Rule(:S, Production[prod1, prod2])
grammar = Grammar([rule1])
grammar.rules[1].non_term
Expr

Expr(1,2,3)

kaka = () -> 3
kaka

kaka()

