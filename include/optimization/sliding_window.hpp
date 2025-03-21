// VolEsti (volume computation and sampling library)

// Copyright (c) 2012-2020 Vissarion Fisikopoulos
// Copyright (c) 2020 Apostolos Chalkis

//Contributed and/or modified by Repouskos Panagiotis, as part of Google Summer of Code 2019 program.

// Licensed under GNU LGPL.3, see LICENCE file

#ifndef VOLESTI_SLIDING_WINDOW_HPP
#define VOLESTI_SLIDING_WINDOW_HPP


/// Computes the relative error
/// \tparam NT Numeric type
/// \param[in] approx The approximated value
/// \param[in] exact The exact value
/// \return The relative error
template <typename NT>
NT relativeError(NT approx, NT exact) {
    return std::fabs((exact - approx) / exact);
}


/// A sliding window, which allows to get the relative error of approximations
/// \tparam NT Numeric type
template<typename NT>
class SlidingWindow {
public:

    /// The stored approximations (newest at front, oldest at back)
    std::list<NT> approximations;
    /// The size of the window
    int windowSize;
    /// The number of entries in list approximations
    int numEntries;

    /// Constructor
    /// \param[in] windowSize The size of the window
    SlidingWindow(int windowSize) : windowSize(windowSize) {
        numEntries = 0;
    }

    /// Adds a new approximation to the front of the window
    /// If the window is full, the oldest approximation will be removed
    /// \param[in] approximation The new approximation to add
    void push(NT approximation) {
        // if window is full, remove the oldest value
        if (numEntries >= windowSize) {
            approximations.pop_back();
        }
        else {
            numEntries++;
        }

        approximations.push_front(approximation);
    }

    /// Calculates the relative error between the newest and oldest approximations
    /// \return The relative error |newest - oldest| / |newest| if the window is full, otherwise returns 1.0
    double getRelativeError() {
        if (numEntries < windowSize)
            return 1;

        // Calculate relative error: |newest - oldest| / |newest|
        return relativeError(approximations.front(), approximations.back());
    }
};

#endif //VOLESTI_SLIDING_WINDOW_HPP
