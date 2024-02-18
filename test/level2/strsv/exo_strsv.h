#pragma once

#include <cblas.h>

#include "exo_trsv.h"

void exo_strsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
               const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
               const int N, const float *A, const int lda, float *X,
               const int incX) {
  if (order != CBLAS_ORDER::CblasRowMajor) {
    throw "Unsupported Exception";
  }
  if (incX < 0) {
    X = X + (1 - N) * incX;
  }
  if (Uplo == CBLAS_UPLO::CblasUpper) {
    if (TransA == CBLAS_TRANSPOSE::CblasNoTrans) {
      if (incX == 1) {
        exo_strsv_rm_un_stride_1(nullptr, Diag == CBLAS_DIAG::CblasUnit, N,
                                 exo_win_1f32{.data = X, .strides = {incX}},
                                 exo_win_2f32c{.data = A, .strides = {lda, 1}});
      } else {
        exo_strsv_rm_un_stride_any(
            nullptr, Diag == CBLAS_DIAG::CblasUnit, N,
            exo_win_1f32{.data = X, .strides = {incX}},
            exo_win_2f32c{.data = A, .strides = {lda, 1}});
      }
    } else {
      if (incX == 1) {
        exo_strsv_rm_ut_stride_1(nullptr, Diag == CBLAS_DIAG::CblasUnit, N,
                                 exo_win_1f32{.data = X, .strides = {incX}},
                                 exo_win_2f32c{.data = A, .strides = {lda, 1}});
      } else {
        exo_strsv_rm_ut_stride_any(
            nullptr, Diag == CBLAS_DIAG::CblasUnit, N,
            exo_win_1f32{.data = X, .strides = {incX}},
            exo_win_2f32c{.data = A, .strides = {lda, 1}});
      }
    }
  } else {
    if (TransA == CBLAS_TRANSPOSE::CblasNoTrans) {
      if (incX == 1) {
        exo_strsv_rm_ln_stride_1(nullptr, Diag == CBLAS_DIAG::CblasUnit, N,
                                 exo_win_1f32{.data = X, .strides = {incX}},
                                 exo_win_2f32c{.data = A, .strides = {lda, 1}});
      } else {
        exo_strsv_rm_ln_stride_any(
            nullptr, Diag == CBLAS_DIAG::CblasUnit, N,
            exo_win_1f32{.data = X, .strides = {incX}},
            exo_win_2f32c{.data = A, .strides = {lda, 1}});
      }
    } else {
      if (incX == 1) {
        exo_strsv_rm_lt_stride_1(nullptr, Diag == CBLAS_DIAG::CblasUnit, N,
                                 exo_win_1f32{.data = X, .strides = {incX}},
                                 exo_win_2f32c{.data = A, .strides = {lda, 1}});
      } else {
        exo_strsv_rm_lt_stride_any(
            nullptr, Diag == CBLAS_DIAG::CblasUnit, N,
            exo_win_1f32{.data = X, .strides = {incX}},
            exo_win_2f32c{.data = A, .strides = {lda, 1}});
      }
    }
  }
}
