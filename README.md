# Class of Life Simulator

A C++ program simulating biological entities including genomes, cells, animals, and viruses, featuring genetic operations and inheritance mechanisms.

## Methodology

This project implements fundamental biological concepts through object-oriented programming. Key algorithms and data structures include:

- **Inheritance Hierarchy**: Genome → Cell → Animal, with Virus inheriting from Genome, demonstrating polymorphism and encapsulation.
- **Genetic Similarity Algorithm**: Calculates percentage similarity between animals based on chromosome count and nucleotide matching, using string comparison loops.
- **Mutation Algorithms**:
  - Small mutation: Replaces n occurrences of a nucleotide using linear search.
  - Great mutation: Substring replacement with KMP algorithm for efficient pattern finding.
  - Reverse mutation: In-place string reversal of matched substrings.
- **Reproduction Algorithms**:
  - Asexual: Random selection of 70% chromosomes using set-based sampling.
  - Sexual: Combines chromosomes from compatible parents (similarity ≥70%) with random crossover.
- **Palindrome Detection**: Nested loops to find complementary palindromic sequences in DNA strands.
- **Health Assessment**: Evaluates nucleotide mismatches and AT/CG ratios to determine cell/animal viability.
- **KMP Algorithm**: Optimized string matching for substring searches in genetic sequences.

## Technologies Used

- **Language**: C++
- **Standard Library**: Vectors, strings, sets, algorithms
- **Randomization**: rand() for genetic variation simulations

## Features

- Create and manage genomes with RNA and complementary DNA pairs
- Perform various genetic mutations on genomes and chromosomes
- Build cells from multiple genomes and check cellular health
- Simulate animal reproduction (asexual and sexual) with genetic similarity checks
- Detect DNA palindromes in chromosomes
- Create viruses that can harm animals based on common genetic substrings
- Interactive menu-driven interface for all operations

## Quick Start

```bash
git clone <repository-url>
cd class-of-life
g++ main.cpp animal.cpp cell.cpp -o simulator
./simulator
```

## Project Structure

```mermaid
graph TD
    A[main.cpp] --> B[animal.h]
    A --> C[cell.h]
    B --> C
    C --> D[genome class]
    B --> E[Animal class]
    B --> F[virus class]
    C --> G[cell class]

    D --> H[RNA string]
    D --> I[DNA array[2]]
    D --> J[Mutations]

    E --> K[Inherits from cell]
    E --> L[Genetic similarity]
    E --> M[Reproduction]
    E --> N[Health check]

    F --> O[Inherits from genome]
    F --> P[Harm function]

    G --> Q[Inherits from genome]
    G --> R[Chromosome vector]
    G --> S[Mutations]
    G --> T[Palindrome detection]
```
