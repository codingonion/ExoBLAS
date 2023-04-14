#pragma once

#include <cblas.h>

#include "exo_gemm.h"

void exo_dgemm_notranspose(const int m, const int n, const int k,
                           const double *alpha, const double *beta,
                           const double *A, const double *B, double *C) {
  if (*alpha == 1.0 && *beta == 1.0) {
    exo_dgemm_notranspose_noalpha_nobeta_main(nullptr, m, n, k, alpha, beta, A,
                                              B, C);
  } else if (*alpha == 0.0 && *beta == 1.0) {
    return;
  } else if (*alpha == 0.0 && *beta != 1.0) {
    exo_dgemm_alphazero_beta_main(nullptr, m, n, k, alpha, beta, A, B, C);
  } else if (*alpha != 1.0 && *beta == 1.0) {
    exo_dgemm_notranspose_alpha_nobeta_main(nullptr, m, n, k, alpha, beta, A, B,
                                            C);
  } else {
    exo_dgemm_notranspose_alpha_beta_main(nullptr, m, n, k, alpha, beta, A, B,
                                          C);
  }
}

void exo_dgemm_transa(const int m, const int n, const int k,
                      const double *alpha, const double *beta, const double *A,
                      const double *B, double *C) {
  if (*alpha == 1.0 && *beta == 1.0) {
    exo_dgemm_transa_noalpha_nobeta_main(nullptr, m, n, k, alpha, beta, A, B,
                                         C);
  } else if (*alpha == 0.0 && *beta == 1.0) {
    return;
  } else if (*alpha == 0.0 && *beta != 1.0) {
    exo_dgemm_alphazero_beta_main(nullptr, m, n, k, alpha, beta, A, B, C);
  } else if (*alpha != 1.0 && *beta == 1.0) {
    exo_dgemm_transa_alpha_nobeta_main(nullptr, m, n, k, alpha, beta, A, B, C);
  } else {
    exo_dgemm_transa_alpha_beta_main(nullptr, m, n, k, alpha, beta, A, B, C);
  }
}

void exo_dgemm_transb(const int m, const int n, const int k,
                      const double *alpha, const double *beta, const double *A,
                      const double *B, double *C) {
  if (*alpha == 1.0 && *beta == 1.0) {
    exo_dgemm_transb_noalpha_nobeta_main(nullptr, m, n, k, alpha, beta, A, B,
                                         C);
  } else if (*alpha == 0.0 && *beta == 1.0) {
    return;
  } else if (*alpha == 0.0 && *beta != 1.0) {
    exo_dgemm_alphazero_beta_main(nullptr, m, n, k, alpha, beta, A, B, C);
  } else if (*alpha != 1.0 && *beta == 1.0) {
    exo_dgemm_transb_alpha_nobeta_main(nullptr, m, n, k, alpha, beta, A, B, C);
  } else {
    exo_dgemm_transb_alpha_beta_main(nullptr, m, n, k, alpha, beta, A, B, C);
  }
}

void exo_dgemm_transa_transb(const int m, const int n, const int k,
                             const double *alpha, const double *beta,
                             const double *A, const double *B, double *C) {
  if (*alpha == 1.0 && *beta == 1.0) {
    exo_dgemm_transa_transb_noalpha_nobeta_main(nullptr, m, n, k, alpha, beta,
                                                A, B, C);
  } else if (*alpha == 0.0 && *beta == 1.0) {
    return;
  } else if (*alpha == 0.0 && *beta != 1.0) {
    exo_dgemm_alphazero_beta_main(nullptr, m, n, k, alpha, beta, A, B, C);
  } else if (*alpha != 1.0 && *beta == 1.0) {
    exo_dgemm_transa_transb_alpha_nobeta_main(nullptr, m, n, k, alpha, beta, A,
                                              B, C);
  } else {
    exo_dgemm_transa_transb_alpha_beta_main(nullptr, m, n, k, alpha, beta, A, B,
                                            C);
  }
}

void exo_dgemm(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE transa,
               const enum CBLAS_TRANSPOSE transb, const int m, const int n,
               const int k, const double *alpha, const double *beta,
               const double *A, const double *B, double *C) {
  if (order == CblasColMajor) {
    throw "Unsupported Exception";
  } else {
    if (transa == CblasNoTrans && transb == CblasNoTrans) {
      exo_dgemm_notranspose(m, n, k, alpha, beta, A, B, C);
    } else if (transa == CblasTrans && transb == CblasNoTrans) {
      exo_dgemm_transa(m, n, k, alpha, beta, A, B, C);
    } else if (transa == CblasNoTrans && transb == CblasTrans) {
      exo_dgemm_transb(m, n, k, alpha, beta, A, B, C);
    } else {
      exo_dgemm_transa_transb(m, n, k, alpha, beta, A, B, C);
    }
  }
}
