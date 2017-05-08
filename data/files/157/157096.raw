# Following Gaussian Process Topic Models:
# http://event.cwi.nl/uai2010/papers/UAI2010_0184.pdf
# with some slight simplifications (we constrain the noise to be  Sigma = I s^-2)

# K - number of topics
# D - number of documents
# V - vocabulary size
#
# Parameters to be learned:
# Beta - KxV matrix of topic/word probabilities
# F - DxK matrix of document topic distribution means
# s - inverse noise variance / noise precision (scalar, assuming equal variance white noise)
#
# Variational parameters to be optimised (as approximate inference for latent variables):
# Phi -- VxDxK -- (sparse in all but K) parameter vectors of discrete factors over topic allocations for occurences of each distinct word in each document
# Lambda -- DxK -- mean parameters of gaussian factors over log-domain document topic proportions eta_dk
# Nu2 -- DxK -- variance parameters of same
# Zeta -- D -- per-document auxiliary variable
#
# Data and fixed parameters:
# W -- sparse VxD -- sparse word count matrix
#
# X -- D x 2 -- geographical coordinates for documents (only used to compute kernel matrix)
# tau -- scale parameter of gaussian process
# sigma2 -- noise variance (scalar)
# Kappa - DxD kernel matrix over documents computed from X and tau

function gaussian_kernel_matrix(data, tau)
    function(i :: Int, j :: Int)
        exp(- sum((data[i,:] - data[j,:]) .^ 2) / (2*tau^2))
    end
end

function fitmodel(W :: SparseMatrixCSC{Uint32,Uint32},
                  X :: Matrix{Float32},
                  K :: Uint32,
                  tau :: Float32)
    (V,D) = size(W)
    @assert size(X) == (D, 2)

    doc_words = Array(Vector{Uint32}, D)
    doc_wordcounts = Array(Vector{Uint32}, D)
    doc_totals :: Vector{Uint32} = zeros(D)
    Phi = Array(Matrix{Float32}, D)
    for d = 1:D
        colrange = W.colptr[d] : W.colptr[d+1]-1
        doc_words[d] = W.rowval[colrange]
        doc_wordcounts[d] = W.nzval[colrange]
        doc_totals[d] = length(colrange)
        Phi[d] = zeros(K, length(colrange))
    end

    Kappa = kernelmatrix(X, tau)

    Beta :: Matrix{Float32} = zeros(K,V)
    F :: Matrix{Float32} = zeros(D,K)
    Lambda :: Matrix{Float32} = zeros(D,K)
    Nu2 :: Matrix{Float32} = zeros(D,K)
    Zeta :: Vector{Float32} = zeros(D)
    s

    while true

        # Update for beta
        Beta[:,:] = 0
        for d = 1:D
            wc = doc_wordcounts[d]
            w = doc_words[d]
            phi_d = Phi[d]
            for i = 1:length(w)
                Beta[:, w[i]] += wc[i] * phi_d[:, i]
            end
        end
        Beta ./= sum(Beta, 2)

        # Update for Phi
        for d = 1:D
            w = doc_words[d]
            phi_d = Phi[d]
            for i = 1:length(w)
                p = exp(Lambda[d,:]) .* Beta[:, w[i]]
                phi_d[:, i] = p
                phi_d[:, i] /= sum(p)
            end
        end

        # Update for Zeta
        exp_lambda_nu = exp(Lambda + Nu2/2) # this will be useful in the lambda update too
        Zeta = sum(exp_lambda_nu, 2)

        # Update for lambda. This is a coordinate-wise newton update, which is easier when Sigma = I.
        N_over_Zeta_exp_lambda_nu = (exp_lambda_nu .*= (doc_totals ./ Zeta))

        sum_phi :: Matrix{Float32} = zeros(D,K)
        for d = 1:D
            sum_phi[d, :] = Phi[d] * doc_wordcounts[d]
        end
        # -= first deriv / second deriv
        Lambda_deriv = -s * (Lambda - F) + sum_phi - N_over_Zeta_exp_lambda_nu
        Lambda_2deriv = -s - N_over_Zeta_exp_lambda_nu
        Lambda -= Lambda_deriv ./ Lambda_2deriv

        # Coordinate-wise newton Update for Nu^2
        Nu2_deriv = -s/2 - N_over_Zeta_exp_lambda_nu/2 + Nu2/2
        Nu2_deriv2 = -N_over_Zeta_exp_lambda_nu/4 - (Nu2 .^ 2)/2
        Nu2 -= Nu2_deriv ./ Nu2_deriv2

        # Update for the noise precision s (simpler than for the full covariance Sigma)
        # (TODO: we could learn separate diagonal entries for the noise covariance, might give an ARD effect. worthwhile?)
        s = mean(Nu2 + (Lambda - F) .^ 2)

        # Update for F
        Kappa_noise = copy(Kappa); Kappa_noise[diagind(Kappa_noise)] += 1/s
        F = (Lambda' * Kappa) / Kappa_noise

        # TODO: convergence check?
    end
end

# Simpler version in which eta is marginalised out, rather than
# variational inference done for it. This is possible without the
# row/column dependency issues the paper mentions when the noise Sigma
# is iid normal.
# In this case though, it's not so easy to learn the noise level, so you have to specify it upfront.
# (Not impossible though, could derive gradient-based updates for it given the eigenvalues of the kernel)

function fitmodel(W :: SparseMatrixCSC{Uint32,Uint32},
                  X :: Matrix{Float32},
                  K :: Uint32,
                  tau :: Float32,
                  sigma2 :: Float32)
    (V,D) = size(W)
    @assert size(X) == (D, 2)

    doc_words = Array(Vector{Uint32}, D)
    doc_wordcounts = Array(Vector{Uint32}, D)
    doc_totals :: Vector{Uint32} = zeros(D)
    Phi = Array(Matrix{Float32}, D)
    for d = 1:D
        colrange = W.colptr[d] : W.colptr[d+1]-1
        doc_words[d] = W.rowval[colrange]
        doc_wordcounts[d] = W.nzval[colrange]
        doc_totals[d] = length(colrange)
        Phi[d] = zeros(K, length(colrange))
    end

    Kappa = kernelmatrix(X, tau)
    Kappa[diagind(Kappa)] += sigma2

    Beta :: Matrix{Float32} = zeros(K,V)
    F :: Matrix{Float32} = zeros(D,K)
    Zeta :: Vector{Float32} = zeros(D)

    while true

        # Update for beta
        Beta[:,:] = 0
        for d = 1:D
            wc = doc_wordcounts[d]
            w = doc_words[d]
            phi_d = Phi[d]
            for i = 1:length(w)
                Beta[:, w[i]] += wc[i] * phi_d[:, i]
            end
        end
        Beta ./= sum(Beta, 2)

        # Update for Phi
        for d = 1:D
            w = doc_words[d]
            phi_d = Phi[d]
            for i = 1:length(w)
                p = exp(F[d,:]) .* Beta[:, w[i]]
                phi_d[:, i] = p
                phi_d[:, i] /= sum(p)
            end
        end

        # Update for Zeta
        exp_F = exp(F)
        Zeta = sum(exp_F, 2)

        # Update for F -- no exact form this time so a componentwise newton:
        sum_phi :: Matrix{Float32} = zeros(D,K)
        for d = 1:D
            sum_phi[d, :] = Phi[d] * doc_wordcounts[d]
        end

        exp_F_N_over_Zeta = exp_F .* (doc_totals ./ Zeta)
        F_deriv = - (F / Kappa) + sum_phi - exp_F_N_over_Zeta
        F_deriv2 = - exp_F_N_over_Zeta + diag(inv(Kappa)) # TODO get this from cholesky and use cholesky above too
        F -= F_deriv ./ F_deriv2

        # TODO: convergence check?
    end
end


# Even simpler still in which there's just one latent topic per document.
# This is a mixture model not an admixture model.
# The topic/word distributions are integrated out here and we use a collapsed
# variational bayes approach to inference
function fitmodel(W :: SparseMatrixCSC{Uint32,Uint32},
                  X :: Matrix{Float32},
                  K :: Uint32,
                  tau :: Float32,
                  sigma2 :: Float32,
                  T :: Int # dimensionality of low-rank kernel approx
                  )
    (V,D) = size(W)
    @assert size(X) == (D, 2)

    doc_words = Array(Vector{Uint32}, D)
    doc_wordcounts = Array(Vector{Uint32}, D)
    doc_totals :: Vector{Uint32} = zeros(D)
    for d = 1:D
        colrange = W.colptr[d] : W.colptr[d+1]-1
        doc_words[d] = W.rowval[colrange]
        doc_wordcounts[d] = W.nzval[colrange]
        doc_totals[d] = length(colrange)
    end

    # Approx cholesky decomp of kernel matrix.
    # Actual kernel once white noise added is L^T L + sigma^2 I.
    # But we use woodbury identities etc, don't directly compute it.
    L = ichol(gaussian_kernel_matrix(X, tau), D, T)

    M = (1/sigma2) * L*L'
    M[diagind(M)] += 1
    B = chol(M)
    C = L' / B
    # so now K^-1 approx= sigma^-2 I - sigma^-4 C C^T.
    # we precompute the diagonal of K^-1 for use in newton updates:
    K_inv_diag = sigma2^-1 - sigma2^-2 * sum(C .^ 2, 2)

    F :: Matrix{Float32} = zeros(D,K)
    Zeta :: Vector{Float32} = zeros(D)
    Q :: Matrix{Float32} = zeros(D,K)

    while true

        # Update for beta
        Beta[:,:] = 0
        for d = 1:D
            wc = doc_wordcounts[d]
            w = doc_words[d]
            # todo rewrite this as a dense by sparse mx mult?
            for i = 1:length(w)
                Beta[:, w[i]] += wc[i] * Phi[d,:]
            end
        end
        Beta ./= sum(Beta, 2)

        # Update for Phi
        for d = 1:D
            w = doc_words[d]
            for i = 1:length(w)
                p = exp(F[d,:]) .* Beta[:, w[i]]
                Phi[d,:] = p
                Phi[d,:] /= sum(p)
            end
        end

        # Update for Zeta
        exp_F = exp(F)
        Zeta = sum(exp_F, 2)
        exp_F_over_Zeta = exp_F ./ Zeta

        # Update for F -- no exact form this time. A componentwise newton
        # (i.e. which approximates the hessian by its diagonal) update is fairly quick:

        invK_F = sigma2^-1 * F - sigma2^-2 * (C * (C' * F))
        F_gradient = - invK_F + Q - exp_F_over_Zeta
        F_hessian_diags = - K_inv_diag - exp_F_over_Zeta

        F -= F_gradient ./ F_hessian_diags

        # Full newton updates for F would be O(K D T^2)
        # as opposed to O(KDT) for componentwise newton:
        if false
            for k in 1:K
                Lambda_inv = 1 ./ (exp_F_over_Zeta[:,k] + sigma2^-1)
                Lambda_inv_Fgradk = Lambda_inv .* F_gradient[:,k]

                update = Lambda_inv .* F_gradient[:,k]
                update = L * update
                update = (M + (L.*Lambda_inv)*L') \ update # will \ use cholesky here?
                update = L' * update
                update = F_gradient[:, k] + update
                update = Lambda_inv .* update
                F[:,k] += update
            end
        end

        # Update for Q
        sums = zeros(K,W)
        for d = 1:D
            sums[:, doc_words[d]] += Q[d,:] * doc_wordcounts[d]
        end
        margin_sums = sum(sums, 2)

        for d = 1:D
            sums[:, doc_words[d]] -= Q[d,:] * doc_wordcounts[d]
            margin_sums[d] -= sum(Q[d,:] * doc_wordcounts[d])

            # words in D by K, then sum along words to get K
            log_qd = sum(gammaln(beta + doc_wordcounts[d] + sums), 1) -
              gammaln(V*beta + doc_totals[d] + margin_sums) +
              F[d,:]

            Q[d,:] = softmax(log_qd)

            # after updating Q[d,:], add it back:
            sums[:, doc_words[d]] -= Q[d,:] * doc_wordcounts[d]
            margin_sums[d] += sum(Q[d,:] * doc_wordcounts[d])
        end

        # TODO: convergence check?
    end
end
