# Benchmark
컴퓨팅 리소스 및 가상 머신의 성능을 측정하기 위한 저장소입니다.

## Introduction
High-performance computing을 위한 다양한 Benchmark 및 프로그램 예제

<br>

## Contents

### C

  * SAXPY <br>
 SAXPY는 Single-Precision A·X Plus Y를 정의한 벤치마크 프로그램<br>
기본 루프는 다음과 같다.<br>
```c
for (int i = 0; i < n; ++i)
  y[i] = a*x[i] + y[i];
```

  * Gaussian <br>
단위행렬 계산 및 Gauss-Jordan Elimination의 적용한 프로그램<br>

