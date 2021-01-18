/******************************************************************************
 * Copyright 1998-2019 Lawrence Livermore National Security, LLC and other
 * HYPRE Project Developers. See the top-level COPYRIGHT file for details.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR MIT)
 ******************************************************************************/

/******************************************************************************
 *
 * Member functions for hypre_Vector class.
 *
 *****************************************************************************/

#include "seq_mv.h"
#include <assert.h>

/*--------------------------------------------------------------------------
 * hypre_SeqVectorCreate
 *--------------------------------------------------------------------------*/

hypre_Vector *
hypre_SeqVectorCreate( HYPRE_Int size )
{
   hypre_Vector  *vector;

   vector = hypre_CTAlloc(hypre_Vector, 1, HYPRE_MEMORY_HOST);

   hypre_VectorData(vector) = NULL;
   hypre_VectorSize(vector) = size;

   hypre_VectorNumVectors(vector) = 1;
   hypre_VectorMultiVecStorageMethod(vector) = 0;

   /* set defaults */
   hypre_VectorOwnsData(vector) = 1;

   hypre_VectorMemoryLocation(vector) = HYPRE_MEMORY_SHARED;

   return vector;
}

/*--------------------------------------------------------------------------
 * hypre_SeqMultiVectorCreate
 *--------------------------------------------------------------------------*/

hypre_Vector *
hypre_SeqMultiVectorCreate( HYPRE_Int size, HYPRE_Int num_vectors )
{
   hypre_Vector *vector = hypre_SeqVectorCreate(size);
   hypre_VectorNumVectors(vector) = num_vectors;

   return vector;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorDestroy
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_SeqVectorDestroy( hypre_Vector *vector )
{
   HYPRE_Int ierr=0;

   if (vector)
   {
      HYPRE_Int memory_location = hypre_VectorMemoryLocation(vector);

      if ( hypre_VectorOwnsData(vector) )
      {
         hypre_TFree(hypre_VectorData(vector), memory_location);
      }

      hypre_TFree(vector, HYPRE_MEMORY_HOST);
   }

   return ierr;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorInitialize
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_SeqVectorInitialize_v2( hypre_Vector *vector, HYPRE_Int memory_location )
{
   HYPRE_Int  size = hypre_VectorSize(vector);
   HYPRE_Int  ierr = 0;
   HYPRE_Int  num_vectors = hypre_VectorNumVectors(vector);
   HYPRE_Int  multivec_storage_method = hypre_VectorMultiVecStorageMethod(vector);

   hypre_VectorMemoryLocation(vector) = memory_location;

   /* Caveat: for pre-existing data, the memory location must be guaranteed
    * to be consistent with `memory_location'
    * Otherwise, mismatches will exist and problems will be encountered
    * when being used, and freed */
   if ( !hypre_VectorData(vector) )
   {
      hypre_VectorData(vector) = hypre_CTAlloc(HYPRE_Complex, num_vectors*size,
                                               memory_location);
   }

   if ( multivec_storage_method == 0 )
   {
      hypre_VectorVectorStride(vector) = size;
      hypre_VectorIndexStride(vector) = 1;
   }
   else if ( multivec_storage_method == 1 )
   {
      hypre_VectorVectorStride(vector) = 1;
      hypre_VectorIndexStride(vector) = num_vectors;
   }
   else
   {
      ++ierr;
   }

   return ierr;
}

HYPRE_Int
hypre_SeqVectorInitialize( hypre_Vector *vector )
{
   HYPRE_Int ierr;

   ierr = hypre_SeqVectorInitialize_v2( vector, hypre_VectorMemoryLocation(vector) );

   return ierr;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorSetDataOwner
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_SeqVectorSetDataOwner( hypre_Vector *vector,
                             HYPRE_Int     owns_data   )
{
   HYPRE_Int    ierr=0;

   hypre_VectorOwnsData(vector) = owns_data;

   return ierr;
}

/*--------------------------------------------------------------------------
 * ReadVector
 *--------------------------------------------------------------------------*/

hypre_Vector *
hypre_SeqVectorRead( char *file_name )
{
   hypre_Vector  *vector;

   FILE    *fp;

   HYPRE_Complex *data;
   HYPRE_Int      size;

   HYPRE_Int      j;

   /*----------------------------------------------------------
    * Read in the data
    *----------------------------------------------------------*/

   fp = fopen(file_name, "r");

   hypre_fscanf(fp, "%d", &size);

   vector = hypre_SeqVectorCreate(size);
   hypre_SeqVectorInitialize(vector);

   data = hypre_VectorData(vector);
   for (j = 0; j < size; j++)
   {
      hypre_fscanf(fp, "%le", &data[j]);
   }

   fclose(fp);

   /* multivector code not written yet >>> */
   hypre_assert( hypre_VectorNumVectors(vector) == 1 );

   return vector;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorPrint
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_SeqVectorPrint( hypre_Vector *vector,
                      char         *file_name )
{
   FILE    *fp;

   HYPRE_Complex *data;
   HYPRE_Int      size, num_vectors, vecstride, idxstride;

   HYPRE_Int      i, j;
   HYPRE_Complex  value;

   HYPRE_Int      ierr = 0;

   num_vectors = hypre_VectorNumVectors(vector);
   vecstride = hypre_VectorVectorStride(vector);
   idxstride = hypre_VectorIndexStride(vector);

   /*----------------------------------------------------------
    * Print in the data
    *----------------------------------------------------------*/

   data = hypre_VectorData(vector);
   size = hypre_VectorSize(vector);

   fp = fopen(file_name, "w");

   if ( hypre_VectorNumVectors(vector) == 1 )
   {
      hypre_fprintf(fp, "%d\n", size);
   }
   else
   {
      hypre_fprintf(fp, "%d vectors of size %d\n", num_vectors, size );
   }

   if ( num_vectors>1 )
   {
      for ( j=0; j<num_vectors; ++j )
      {
         hypre_fprintf(fp, "vector %d\n", j );
         for (i = 0; i < size; i++)
         {
            value = data[ j*vecstride + i*idxstride ];
#ifdef HYPRE_COMPLEX
            hypre_fprintf(fp, "%.14e , %.14e\n",
                          hypre_creal(value), hypre_cimag(value));
#else
            hypre_fprintf(fp, "%.14e\n", value);
#endif
         }
      }
   }
   else
   {
      for (i = 0; i < size; i++)
      {
#ifdef HYPRE_COMPLEX
         hypre_fprintf(fp, "%.14e , %.14e\n",
                       hypre_creal(data[i]), hypre_cimag(data[i]));
#else
         hypre_fprintf(fp, "%.14e\n", data[i]);
#endif
      }
   }

   fclose(fp);

   return ierr;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorSetConstantValues
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_SeqVectorSetConstantValues( hypre_Vector *v,
                                  HYPRE_Complex value )
{
#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] -= hypre_MPI_Wtime();
#endif

   HYPRE_Complex *vector_data = hypre_VectorData(v);
   HYPRE_Int      size        = hypre_VectorSize(v);
   HYPRE_Int      ierr  = 0;

   size *= hypre_VectorNumVectors(v);

   hypre_SeqVectorPrefetch(v, HYPRE_MEMORY_DEVICE);

#if defined(HYPRE_USING_CUDA)
   HYPRE_THRUST_CALL( fill_n, vector_data, size, value );
#else
   HYPRE_Int i;
#if defined(HYPRE_USING_DEVICE_OPENMP)
#pragma omp target teams distribute parallel for private(i) is_device_ptr(vector_data)
#elif defined(HYPRE_USING_OPENMP)
#pragma omp parallel for private(i) HYPRE_SMP_SCHEDULE
#endif
   for (i = 0; i < size; i++)
   {
      vector_data[i] = value;
   }
#endif /* defined(HYPRE_USING_CUDA) */

   hypre_SyncCudaComputeStream(hypre_handle);

#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] += hypre_MPI_Wtime();
#endif

   return ierr;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorSetRandomValues
 *
 *     returns vector of values randomly distributed between -1.0 and +1.0
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_SeqVectorSetRandomValues( hypre_Vector *v,
                                HYPRE_Int     seed )
{
   HYPRE_Complex *vector_data = hypre_VectorData(v);
   HYPRE_Int      size        = hypre_VectorSize(v);
   HYPRE_Int      i;
   HYPRE_Int      ierr  = 0;
   hypre_SeedRand(seed);

   size *= hypre_VectorNumVectors(v);

   /* RDF: threading this loop may cause problems because of hypre_Rand() */
   for (i = 0; i < size; i++)
   {
      vector_data[i] = 2.0 * hypre_Rand() - 1.0;
   }

   return ierr;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorCopy
 * copies data from x to y
 * if size of x is larger than y only the first size_y elements of x are
 * copied to y
 *--------------------------------------------------------------------------*/
HYPRE_Int
hypre_SeqVectorCopy( hypre_Vector *x,
                     hypre_Vector *y )
{
#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] -= hypre_MPI_Wtime();
#endif

   hypre_SeqVectorPrefetch(x, HYPRE_MEMORY_DEVICE);
   hypre_SeqVectorPrefetch(y, HYPRE_MEMORY_DEVICE);

   HYPRE_Complex *x_data = hypre_VectorData(x);
   HYPRE_Complex *y_data = hypre_VectorData(y);
   HYPRE_Int      size   = hypre_VectorSize(x);
   HYPRE_Int      size_y = hypre_VectorSize(y);
   HYPRE_Int      ierr = 0;

   if (size > size_y)
   {
      size = size_y;
   }
   size *= hypre_VectorNumVectors(x);

#if defined(HYPRE_USING_CUDA)
   HYPRE_THRUST_CALL( copy_n, x_data, size, y_data );
#else
   HYPRE_Int i;
#if defined(HYPRE_USING_DEVICE_OPENMP)
#pragma omp target teams distribute parallel for private(i) is_device_ptr(y_data,x_data)
#elif defined(HYPRE_USING_OPENMP)
#pragma omp parallel for private(i) HYPRE_SMP_SCHEDULE
#endif
   for (i = 0; i < size; i++)
   {
      y_data[i] = x_data[i];
   }
#endif /* defined(HYPRE_USING_CUDA) */

   hypre_SyncCudaComputeStream(hypre_handle);

#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] += hypre_MPI_Wtime();
#endif

   return ierr;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorCloneDeep
 * Returns a complete copy of x - a deep copy, with its own copy of the data.
 *--------------------------------------------------------------------------*/

hypre_Vector*
hypre_SeqVectorCloneDeep( hypre_Vector *x )
{
   HYPRE_Int      size          = hypre_VectorSize(x);
   HYPRE_Int      num_vectors   = hypre_VectorNumVectors(x);

   hypre_Vector *y = hypre_SeqMultiVectorCreate( size, num_vectors );

   hypre_VectorMultiVecStorageMethod(y) = hypre_VectorMultiVecStorageMethod(x);
   hypre_VectorVectorStride(y) = hypre_VectorVectorStride(x);
   hypre_VectorIndexStride(y) = hypre_VectorIndexStride(x);

   hypre_SeqVectorInitialize(y);
   hypre_SeqVectorCopy( x, y );

   return y;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorCloneShallow
 * Returns a complete copy of x - a shallow copy, pointing the data of x
 *--------------------------------------------------------------------------*/

hypre_Vector *
hypre_SeqVectorCloneShallow( hypre_Vector *x )
{
   HYPRE_Int      size   = hypre_VectorSize(x);
   HYPRE_Int      num_vectors   = hypre_VectorNumVectors(x);
   hypre_Vector * y = hypre_SeqMultiVectorCreate( size, num_vectors );

   hypre_VectorMultiVecStorageMethod(y) = hypre_VectorMultiVecStorageMethod(x);
   hypre_VectorVectorStride(y) = hypre_VectorVectorStride(x);
   hypre_VectorIndexStride(y) = hypre_VectorIndexStride(x);

   hypre_VectorData(y) = hypre_VectorData(x);
   hypre_SeqVectorSetDataOwner( y, 0 );
   hypre_SeqVectorInitialize(y);

   return y;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorScale
 *--------------------------------------------------------------------------*/
HYPRE_Int
hypre_SeqVectorScale( HYPRE_Complex alpha,
                      hypre_Vector *y )
{
#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] -= hypre_MPI_Wtime();
#endif

   HYPRE_Complex *y_data = hypre_VectorData(y);
   HYPRE_Int      size   = hypre_VectorSize(y);
   HYPRE_Int      ierr = 0;

   size *= hypre_VectorNumVectors(y);

   hypre_SeqVectorPrefetch(y, HYPRE_MEMORY_DEVICE);

#if defined(HYPRE_USING_CUDA)
   HYPRE_THRUST_CALL( transform, y_data, y_data + size, y_data, alpha * _1 );
#else
   HYPRE_Int i;
#if defined(HYPRE_USING_DEVICE_OPENMP)
#pragma omp target teams distribute parallel for private(i) is_device_ptr(y_data)
#elif defined(HYPRE_USING_OPENMP)
#pragma omp parallel for private(i) HYPRE_SMP_SCHEDULE
#endif
   for (i = 0; i < size; i++)
   {
      y_data[i] *= alpha;
   }

#endif /* defined(HYPRE_USING_CUDA) */

   hypre_SyncCudaComputeStream(hypre_handle);

#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] += hypre_MPI_Wtime();
#endif

   return ierr;
}

/*--------------------------------------------------------------------------
 * hypre_SeqVectorAxpy
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_SeqVectorAxpy( HYPRE_Complex alpha,
                     hypre_Vector *x,
                     hypre_Vector *y     )
{
#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] -= hypre_MPI_Wtime();
#endif

   HYPRE_Complex *x_data = hypre_VectorData(x);
   HYPRE_Complex *y_data = hypre_VectorData(y);
   HYPRE_Int      size   = hypre_VectorSize(x);
   HYPRE_Int      ierr = 0;

   size *= hypre_VectorNumVectors(x);

   hypre_SeqVectorPrefetch(x, HYPRE_MEMORY_DEVICE);
   hypre_SeqVectorPrefetch(y, HYPRE_MEMORY_DEVICE);

#if defined(HYPRE_USING_CUDA)
   HYPRE_THRUST_CALL( transform, x_data, x_data + size, y_data, y_data, alpha * _1 + _2 );
#else
   HYPRE_Int i;
#if defined(HYPRE_USING_DEVICE_OPENMP)
#pragma omp target teams distribute parallel for private(i) is_device_ptr(y_data, x_data)
#elif defined(HYPRE_USING_OPENMP)
#pragma omp parallel for private(i) HYPRE_SMP_SCHEDULE
#endif
   for (i = 0; i < size; i++)
   {
      y_data[i] += alpha * x_data[i];
   }

#endif /* defined(HYPRE_USING_CUDA) */

   hypre_SyncCudaComputeStream(hypre_handle);

#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] += hypre_MPI_Wtime();
#endif

   return ierr;
}


/*--------------------------------------------------------------------------
 * hypre_SeqVectorInnerProd
 *--------------------------------------------------------------------------*/
HYPRE_Real
hypre_SeqVectorInnerProd( hypre_Vector *x,
                          hypre_Vector *y )
{
#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] -= hypre_MPI_Wtime();
#endif

   HYPRE_Complex *x_data = hypre_VectorData(x);
   HYPRE_Complex *y_data = hypre_VectorData(y);
   HYPRE_Int      size   = hypre_VectorSize(x);
   HYPRE_Real     result = 0.0;

   size *= hypre_VectorNumVectors(x);

   hypre_SeqVectorPrefetch(x, HYPRE_MEMORY_DEVICE);
   hypre_SeqVectorPrefetch(y, HYPRE_MEMORY_DEVICE);

#if defined(HYPRE_USING_CUDA)
#ifndef HYPRE_COMPLEX
   result = HYPRE_THRUST_CALL( inner_product, x_data, x_data + size, y_data, 0.0 );
#else
   /* TODO */
#error "Complex inner product"
#endif
#else /* #if defined(HYPRE_USING_CUDA) */
   HYPRE_Int i;
#if defined(HYPRE_USING_DEVICE_OPENMP)
#pragma omp target teams  distribute  parallel for private(i) reduction(+:result) is_device_ptr(y_data,x_data) map(result)
#elif defined(HYPRE_USING_OPENMP)
#pragma omp parallel for private(i) reduction(+:result) HYPRE_SMP_SCHEDULE
#endif
   for (i = 0; i < size; i++)
   {
     result += hypre_conj(y_data[i]) * x_data[i];
   }
#endif /* defined(HYPRE_USING_CUDA) */

   hypre_SyncCudaComputeStream(hypre_handle);

#ifdef HYPRE_PROFILE
   hypre_profile_times[HYPRE_TIMER_ID_BLAS1] += hypre_MPI_Wtime();
#endif

   return result;
}

//TODO

/*--------------------------------------------------------------------------
 * hypre_VectorSumElts:
 * Returns the sum of all vector elements.
 *--------------------------------------------------------------------------*/

HYPRE_Complex hypre_SeqVectorSumElts( hypre_Vector *vector )
{
   HYPRE_Complex  sum = 0;
   HYPRE_Complex *data = hypre_VectorData( vector );
   HYPRE_Int      size = hypre_VectorSize( vector );
   HYPRE_Int      i;

#ifdef HYPRE_USING_OPENMP
#pragma omp parallel for private(i) reduction(+:sum) HYPRE_SMP_SCHEDULE
#endif
   for ( i=0; i<size; ++i ) sum += data[i];

   return sum;
}

HYPRE_Int
hypre_SeqVectorPrefetch( hypre_Vector *x, HYPRE_Int to_location)
{
   HYPRE_Int      ierr = 0;
#ifdef HYPRE_USING_UNIFIED_MEMORY
   HYPRE_Complex *x_data = hypre_VectorData(x);
   HYPRE_Int      size   = hypre_VectorSize(x) * hypre_VectorNumVectors(x);

   if (hypre_GetActualMemLocation(hypre_VectorMemoryLocation(x)) != HYPRE_MEMORY_SHARED)
   {
      /* hypre_error_w_msg(HYPRE_ERROR_GENERIC," Error! CUDA Prefetch with non-unified momory\n");*/
      return ierr;
   }

   if (size == 0)
   {
      return ierr;
   }

   /* speical use of TMemcpy for prefetch */
   hypre_TMemcpy(x_data, x_data, HYPRE_Complex, size, to_location, HYPRE_MEMORY_SHARED);
#endif

   return ierr;
}

//hypre_int hypre_SeqVectorIsManaged(hypre_Vector *x)
//{
//   return pointerIsManaged((void*)hypre_VectorData(x));
//}

