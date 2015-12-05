/*BHEADER**********************************************************************
 * Copyright (c) 2006   The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by the HYPRE team. UCRL-CODE-222953.
 * All rights reserved.
 *
 * This file is part of HYPRE (see http://www.llnl.gov/CASC/hypre/).
 * Please see the COPYRIGHT_and_LICENSE file for the copyright notice, 
 * disclaimer, contact information and the GNU Lesser General Public License.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License (as published by the Free Software
 * Foundation) version 2.1 dated February 1999.
 *
 * HYPRE is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE.  See the terms and conditions of the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * $Revision: 1.3 $
 ***********************************************************************EHEADER*/



/* ******************************************************************** */
/* See the file COPYRIGHT for a complete copyright notice, contact      */
/* person and disclaimer.                                               */        
/* ******************************************************************** */

/* ******************************************************************** */
/* Declaration of matrix-format specific stuff                          */
/* ******************************************************************** */
/* Author        : Charles Tong (LLNL) and Ray Tuminaro (SNL)           */
/* Date          : April,    1999                                       */
/* ******************************************************************** */

#ifndef _MLMATFORMATS_
#define _MLMATFORMATS_


/* ******************************************************************** */
/* Structure used for ML_MSR_getrows and ML_CSR_getrows                 */
/*                                                                      */
/* For CSR matrices, we have                                            */
/*    A(i,j) where 0 <= i < N |    j = columns[k] , A(i,j) = values[k]  */
/*           and   0 <= j < N |    where  rowptr[i] <= k <rowptr[i+1]   */
/*                                                                      */
/* For MSR matrices, we have                                            */
/*    A(i,j) where 0 <= i < N,|    j = columns[k] , A(i,j) = values[k]  */
/*                 i != j ,   |    where  columns[i] <= k < columns[i+1]*/
/*             and 0 <= j < N |                                         */
/*    A(i,i) where 0 <= i < N,|    A(i,j) = values[i]                   */
/* -------------------------------------------------------------------- */

struct ML_CSR_MSRdata 
{
   int    *columns, *rowptr;
   double *values;
                              /*************************************/
  int    Nnz, Nrows, Ncols;   /* Haim's addition. Convenient for GGB */
                              /* implementation of prolongator.      */
                              /* These fields are not normally filled */
                              /* in the rest of ml. */
};

struct ML_vbrdata 
{
   double *val;
};
#include "ml_common.h"
#include "ml_comminfoop.h"

typedef struct ML_Matrix_DCSR_Struct
{
   int           ML_id;
   int           mat_n;
   int           *mat_ia;
   int           *mat_ja;
   double        *mat_a;
   ML_Comm       *comm;
   ML_CommInfoOP *comminfo;

} ML_Matrix_DCSR;

#include "ml_operator.h"

#ifndef ML_CPP
#ifdef __cplusplus
extern "C" {
#endif
#endif


extern void ML_RECUR_CSR_MSRdata_Destroy(ML_Operator *matrix);
extern void ML_OnlyFreeTopLevelDataPtr(void *data);
extern void ML_CSR_MSRdata_Destroy(void *data);
extern void ML_CSR_MSRdata_Destroy_StructOnly(void *data);

extern void ML_restricted_MSR_mult(ML_Operator *matrix, int Nrows,
                                   double b[], double c[], int Nsend);

extern void ML_Scale_CSR(ML_Operator *input_matrix,
                         double scale_factors[], int mult_or_divide);

extern int CSR_getrows(void *data,int N_requested_rows,int requested_rows[],
                       int allocated_space, int columns[], double values[],
                       int row_lengths[]);
extern int CSR_getrow(ML_Operator *data,int N_requested_rows,int requested_rows[],
                       int allocated_space, int columns[], double values[],
                       int row_lengths[]);
extern int sCSR_getrows(ML_Operator *data,int N_requested_rows,int requested_rows[],
                       int allocated_space, int columns[], double values[],
                       int row_lengths[]);
extern int cCSR_getrows(ML_Operator *data, int N_requested_rows, int requested_rows[],
                       int allocated_space, int columns[], double values[],
                       int row_lengths[]);

extern int CSR_get_one_row(ML_Operator *data, int N_requested_rows, int
                           requested_rows[], int allocated_space, int
                           columns[], double values[], int row_lengths[]);

extern int cCSR_trans_matvec(ML_Operator *Amat_in, int ilen, double p[], int olen, 
			     double ap[]);
extern int cCSR_matvec(ML_Operator *Amat_in, int ilen, double p[], int olen, 
		       double ap[]);

extern int CSR_trans_matvec(ML_Operator *Amat_in, int ilen, double p[], int olen, double ap[]);

extern int MSR_get_ones_rows(ML_Operator *data, int N_requested_rows, int requested_rows[],
                       int allocated_space, int columns[], double values[],
                       int row_lengths[]);
extern int MSR_getrows(ML_Operator *data, int N_requested_rows, int requested_rows[],
                       int allocated_space, int columns[], double values[],
                       int row_lengths[]);

extern int MSR_matvec(ML_Operator *Amat, int, double p[], int, double ap[]);

#ifdef WKC
/* WKC -- double * happen to be Epetra_MultiVectors in cognito */
extern int MSR_matvec_WKC(ML_Operator *Amat, int, double *p, int, double *ap);
#endif

extern int CSR_densematvec(ML_Operator *Amat_in, int ilen, double p[], int olen, double ap[]);
extern int CSR_matvec(ML_Operator *Amat, int, double p[], int, double ap[]);
extern int sCSR_trans_matvec(ML_Operator *Amat, int, double p[], int, double ap[]);
extern int CSR_trans_ones_matvec(ML_Operator *Amat, int, double p[], int, double ap[]);
extern int sCSR_matvec(ML_Operator *Amat, int, double p[], int, double ap[]);
extern int CSR_ones_matvec(ML_Operator *Amat, int, double p[], int, double ap[]);
extern int sCSR_ones_matvec(ML_Operator *Amat, int, double p[], int, double ap[]);
extern int localCSR_matvec(void *Amat_in, int ilen, double p[], int olen, 
                           double ap[]);


extern int VBR_cnst_blk_getrows(ML_Operator *data, int N_requested_rows,
                                int requested_rows[], int allocated_space,
                                int columns[], double values[],
                                int row_lengths[]);

extern int VECTOR_getrows(ML_Operator *mat,int N_requested_rows,int requested_rows[],
                          int allocated_space, int columns[], double values[],
                          int row_lengths[]);
extern int ML_MSR2CSR(struct ML_CSR_MSRdata *csr_data, int Nrows,
                          int *Ncolumns);  

extern int  ML_Matrix_DCSR_Create( ML_Matrix_DCSR ** );
extern void ML_Matrix_DCSR_Destroy( ML_Matrix_DCSR * );
extern int  ML_Matrix_DCSR_Set( ML_Matrix_DCSR *,int,int*,int*,double*);
extern int  ML_Matrix_DCSR_Set_Comm(ML_Matrix_DCSR*,ML_CommInfoOP*,ML_Comm*);
extern int  ML_Matrix_DCSR_Getrow(ML_Operator*,int,int*,int,int*,double*,int*);
extern int  ML_Matrix_DCSR_Matvec(ML_Operator *,int,double*,int,double*);

#ifndef ML_CPP
#ifdef __cplusplus
}
#endif
#endif
#endif
