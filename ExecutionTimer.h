// evaluate a a given code scope CPU run time
template<class Resolution = std::chrono::milliseconds> struct ExecutionTimer {
    using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
                                     std::chrono::high_resolution_clock,
                                     std::chrono::steady_clock>;
    Clock::time_point m_start;  // class construct time
    
    explicit constexpr ExecutionTimer() : m_start(Clock::now()) {}
    ~ExecutionTimer() {
        const Clock::time_point end{ Clock::now() };
        std::cout << " elapsed: " << std::chrono::duration_cast<Resolution>(end - m_start).count() << std::endl;
    }
};
