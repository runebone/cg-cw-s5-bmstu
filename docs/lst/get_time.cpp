long bm::get_cpu_time_ns() {
	struct timespec t;
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
		std::cerr << "Невозможно получить время.\n";
		return -1;
	}
	return t.tv_sec * 1000000000LL + t.tv_nsec;
}
