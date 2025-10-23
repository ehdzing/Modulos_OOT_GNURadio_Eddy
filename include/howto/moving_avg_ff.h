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


#ifndef INCLUDED_HOWTO_MOVING_AVG_FF_H
#define INCLUDED_HOWTO_MOVING_AVG_FF_H

#include <howto/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace howto {

    /*!
     * \brief Moving Average (boxcar) filter float→float with length N and scale factor.
     * \ingroup howto
     *
     * Mathematical form (causal):
     *   y[n] = (scale / N) * sum_{k=0}^{N-1} x[n - k]
     *
     * Notes:
     * - Uses set_history(N) to access the last N-1 samples.
     * - DC gain = scale.
     */
    class HOWTO_API moving_avg_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<moving_avg_ff> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of howto::moving_avg_ff.
       *
       * To avoid accidental use of raw pointers, howto::moving_avg_ff's
       * constructor is in a private implementation
       * class. howto::moving_avg_ff::make is the public interface for
       * creating new instances.

       * \brief Factory method for creating new instances of howto::moving_avg_ff.
       * \param N     Window length (N >= 1). Default is 8.
       * \param scale Scale factor. Default is 1.0f.
       */

      static sptr make(int N = 8, float scale = 1.0f);

       /*!
       * \brief Runtime setter for window length N.
       * \param N New window size.
       */
      virtual void set_N(int N) = 0;

      /*!
       * \brief Runtime setter for scale factor.
       * \param s New scale factor.
       */
      virtual void set_scale(float s) = 0;

      /*!
       * \brief Returns current window length N.
       */
      virtual int N() const = 0;

      /*!
       * \brief Returns current scale factor.
       */
      virtual float scale() const = 0;

      // Note: The actual constructor and member variables are implemented
      // in the corresponding *_impl class. This header only defines the API.
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_MOVING_AVG_FF_H */

