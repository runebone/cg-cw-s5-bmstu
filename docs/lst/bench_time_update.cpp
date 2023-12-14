int main() {
    Engine engine;
    engine.initialize();

    while (engine.isRunning()) {
        engine.processInput();

        long start = bm::get_cpu_time_ns();
        engine.update();
        engine.render();
        gRenderTime = bm::get_cpu_time_ns() - start;
    }
    // ...
}
