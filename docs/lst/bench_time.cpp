int main() {
    Engine engine;
    engine.initialize();

    while (engine.isRunning()) {
        engine.processInput();
        engine.update();

        long start = bm::get_cpu_time_ns();
        engine.render();
        gRenderTime = bm::get_cpu_time_ns() - start;
    }
    // ...
}
