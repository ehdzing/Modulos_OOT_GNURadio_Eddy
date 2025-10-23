/* -*- c++ -*- */
/* 
 * Copyright 2025 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_HOWTO_MOVING_AVG_FF_IMPL_H
#define INCLUDED_HOWTO_MOVING_AVG_FF_IMPL_H

#include <howto/moving_avg_ff.h>

namespace gr {
  namespace howto {

    class moving_avg_ff_impl : public moving_avg_ff
    {
     private:
      int   d_N;              // current window length (>= 1)
      float d_scale;          // user scale factor
      float d_scale_over_N;   // cached scale/N to avoid per-sample division
      
     // Recompute cached factors after N or scale changes
      inline void update_cached_gains() {
        const int N = std::max(1, d_N);
        d_scale_over_N = d_scale / static_cast<float>(N);
      }

      // Validate and normalize runtime parameters
      inline static int clamp_N(int N) {
        return std::max(1, N);
      }
      inline static float sanitize_scale(float s) {
        // Guard against NaN/Inf to avoid propagating invalid numbers
        return std::isfinite(s) ? s : 1.0f;
      }
	

     public:
      moving_avg_ff_impl(N );
      ~moving_avg_ff_impl();

      // moving_avg_ff interface
      void   set_N(int N) override;
      void   set_scale(float s) override;
      int    N()     const override { return d_N; }
      float  scale() const override { return d_scale; }	

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_MOVING_AVG_FF_IMPL_H */

