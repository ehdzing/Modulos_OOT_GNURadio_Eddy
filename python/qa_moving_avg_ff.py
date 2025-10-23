#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2025 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import howto_swig as howto

def floats_close(a, b, tol=1e-6):
    a = np.asarray(a, dtype=np.float32)
    b = np.asarray(b, dtype=np.float32)
    if a.shape != b.shape:
        return False
    return np.allclose(a, b, rtol=0, atol=tol)

class qa_moving_avg_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_impulso_N4_scale1(self):
        """
        Caso 1: Impulso.
        x = [1, 0, 0, 0, 0, 0], N=4, scale=1
        Con history(N), salida tiene len(x) - (N-1) = 3 elementos:
        y[0] = (1+0+0+0)/4 = 0.25
        y[1] = (0+0+0+0)/4 = 0
        y[2] = (0+0+0+0)/4 = 0
        """
        N = 4
        scale = 1.0
        src_data = [1.0, 0.0, 0.0, 0.0, 0.0, 0.0]
        expected = [0.25, 0.0, 0.0]

        src = blocks.vector_source_f(src_data, repeat=False)
        dut = howto.moving_avg_ff(N, scale)
        snk = blocks.vector_sink_f()

        self.tb.connect(src, dut)
        self.tb.connect(dut, snk)
        self.tb.run()

        result = snk.data()
        self.assertTrue(
            floats_close(result, expected),
            msg="Impulso N=4 scale=1: esperado {} pero obtuve {}".format(expected, result),
        )

    def test_002_escalon_N4_scale1(self):
        """
        Caso 2: Escalón de unos.
        x = [1]*8, N=4, scale=1
        Salida len = 8 - 3 = 5, todo 1.0 (promedio de 4 unos = 1).
        """
        N = 4
        scale = 1.0
        src_data = [1.0] * 8
        expected = [1.0] * (len(src_data) - (N - 1))

        src = blocks.vector_source_f(src_data, repeat=False)
        dut = howto.moving_avg_ff(N, scale)
        snk = blocks.vector_sink_f()

        self.tb.connect(src, dut)
        self.tb.connect(dut, snk)
        self.tb.run()

        result = snk.data()
        self.assertTrue(
            floats_close(result, expected),
            msg="Escalón N=4 scale=1: esperado {} pero obtuve {}".format(expected, result),
        )

    def test_003_random_vs_convolucion(self):
        """
        Caso 3: Aleatorio comparado con convolución de caja (referencia NumPy).
        Demuestra que tu bloque es un FIR boxcar causal con history(N).
        """
        rng = np.random.RandomState(123)
        N = 8
        scale = 0.5
        src_data = rng.randn(100).astype(np.float32)

        # Referencia: convolución con kernel boxcar causal de longitud N,
        # kernel = (scale/N) * [1,1,...,1] (long N)
        kernel = np.ones(N, dtype=np.float32) * (scale / N)
        full = np.convolve(src_data, kernel, mode="valid")  # produce len = len(x) - N + 1
        expected = full.tolist()

        src = blocks.vector_source_f(src_data.tolist(), repeat=False)
        dut = howto.moving_avg_ff(N, scale)
        snk = blocks.vector_sink_f()

        self.tb.connect(src, dut)
        self.tb.connect(dut, snk)
        self.tb.run()

        result = np.asarray(snk.data(), dtype=np.float32)
        self.assertTrue(
            floats_close(result, expected, tol=1e-5),
            msg="Random vs conv boxcar: max err={}".format(np.max(np.abs(result - np.asarray(expected)))),
        )



if __name__ == '__main__':
    gr_unittest.run(qa_moving_avg_ff, "qa_moving_avg_ff.xml")
