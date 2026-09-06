/**
 * @file sepch.h
 * @brief Precompiled header file for the SinterEngine project.
 * 
 * This header aggregates commonly used standard C++ library headers including
 * I/O, containers, functional utilities, and threading components.
 * Including this file speeds up compilation by precompiling frequently used headers.
 */

#pragma once

// IO
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

// Containers
#include <array>
#include <queue>
#include <set>
#include <stack>
#include <vector>

// Functional
#include <algorithm>
#include <functional>
#include <memory>
#include <optional>

// Utility
#include <chrono>
#include <random>

// Threading
#include <mutex>
#include <thread>