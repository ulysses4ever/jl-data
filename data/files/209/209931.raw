type CvxProblem
    minimize :: Bool # Is it a minimization of maximization problem?
    objective :: CvxExpr
    constraints :: Vector{CvxConstraint}
end

Problem(objective, minimize=true, constraints=[]) =
    CvxProblem(minimize, objective, constraints)
