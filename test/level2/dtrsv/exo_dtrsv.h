#pragma once

#include "exo_trsv.h"
#include <cblas.h>

void exo_dtrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const double *A, const int lda, 
                 double *X, const int incX) {
    if (order != CBLAS_ORDER::CblasRowMajor) {
        throw "Unsupported Exception";
    }
    if (incX < 0) {
        X = X + (1 - N) * incX;
    }
    if (Uplo == CBLAS_UPLO::CblasUpper) {
        if (TransA == CBLAS_TRANSPOSE::CblasNoTrans) {
            if (incX == 1) {
                exo_dtrsv_raw_major_Upper_NoneTrans_stride_1(nullptr, N, 
                    exo_win_1f64{.data = X, .strides = {incX}}, 
                    exo_win_2f64c{.data = A, .strides = {lda, 1}}, Diag == CBLAS_DIAG::CblasUnit);
            } else {
                exo_dtrsv_raw_major_Upper_NoneTrans_stride_any(nullptr, N, 
                    exo_win_1f64{.data = X, .strides = {incX}}, 
                    exo_win_2f64c{.data = A, .strides = {lda, 1}}, Diag == CBLAS_DIAG::CblasUnit);
            }
        } else {
            exo_dtrsv_raw_major_Upper_Trans_stride_any(nullptr, N, 
                exo_win_1f64{.data = X, .strides = {incX}}, 
                exo_win_2f64c{.data = A, .strides = {lda, 1}}, Diag == CBLAS_DIAG::CblasUnit);
        }
    } else {
        if (TransA == CBLAS_TRANSPOSE::CblasNoTrans) {
            if (incX == 1) {
                exo_dtrsv_raw_major_Lower_NoneTrans_stride_1(nullptr, N, 
                    exo_win_1f64{.data = X, .strides = {incX}}, 
                    exo_win_2f64c{.data = A, .strides = {lda, 1}}, Diag == CBLAS_DIAG::CblasUnit);
            } else {
                exo_dtrsv_raw_major_Lower_NoneTrans_stride_any(nullptr, N, 
                    exo_win_1f64{.data = X, .strides = {incX}}, 
                    exo_win_2f64c{.data = A, .strides = {lda, 1}}, Diag == CBLAS_DIAG::CblasUnit);
            }
        } else {
            exo_dtrsv_raw_major_Lower_Trans_stride_any(nullptr, N, 
                exo_win_1f64{.data = X, .strides = {incX}}, 
                exo_win_2f64c{.data = A, .strides = {lda, 1}}, Diag == CBLAS_DIAG::CblasUnit);
        }
    }
}
