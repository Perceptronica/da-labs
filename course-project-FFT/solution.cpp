#include <bits/stdc++.h>
#include <cmath>

#define MINIMP3_IMPLEMENTATION

#include "minimp3/minimp3.h"
#include "minimp3/minimp3_ex.h"

std::vector<short> decoder() {
  mp3dec_t mp3d;
  mp3dec_file_info_t info;
  if (mp3dec_load(&mp3d, "input.mp3", &info, NULL, NULL)) {
    throw std::runtime_error("Decode error");
  }
  std::vector<short> res(info.buffer, info.buffer + info.samples);
  free(info.buffer);
  return res;
}

std::vector<double> HannWindow(size_t sz) {
  std::vector<double> res(sz);
  for (size_t i = 0; i < sz; ++i) {
    res[i] = 0.5 * (1 - cos((2 * M_PI * static_cast<int>(i)) / (sz - 1)));
  }
  return res;
}

void FFT(std::vector<std::complex<double>> &A) {
  size_t n = A.size();
  size_t k = std::log2(n);
  for (size_t i = 0, j = 0; i < n; ++i) {
    if (i < j) {
      std::swap(A[i], A[j]);
    }
    int bit = n >> 1;
    while (j & bit) {
      j ^= bit;
      bit >>= 1;
    }
    j ^= bit;
  }
  for (uint64_t s = 1; s <= k; ++s) {
    uint64_t m = 1 << s; // 2^s
    std::complex<double> w_m = std::polar(1.0, -2 * M_PI / m);
    for (uint64_t k = 0; k < n; k += m) {
      std::complex<double> w = 1;
      for (uint64_t j = 0; j < m / 2; ++j) {
        std::complex<double> t = w * A[k + j + m / 2];
        std::complex<double> u = A[k + j];
        A[k + j] = u + t;
        A[k + j + m / 2] = u - t;
        w = w * w_m;
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<short> data = decoder();
  std::size_t win_size = 4096;
  std::size_t step = 1024;
  std::size_t data_size = data.size();
  std::vector<double> hw = HannWindow(win_size);

  auto start = std::chrono::steady_clock::now();
  for (uint64_t i = 0; i < data_size - win_size; i += step) {
      std::vector<std::complex<double>> a(win_size);
      for (std::size_t j = 0; j < win_size; ++j) {
          a[j] = data[i + j] * hw[j];
      }
      FFT(a);
      double m = 0.0;
      for (auto& num : a) {
          m = std::max(m, std::abs(num));
      }
      //std::cout << std::fixed << std::setprecision(20) << m << "\n";
  }
  auto end = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "[FFT_BENCH] Done in " << duration.count() << " microseconds."
            << std::endl;
}
