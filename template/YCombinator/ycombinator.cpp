// Y Combinator for recursive calls
template <typename Func>
struct y_combinator_result {
    Func func;
    template <typename... Args>
    decltype(auto) operator()(Args&&... args) {
        return func(*this, std::forward<Args>(args)...);
    }
};
//Usage: auto func_name = y_combinator([](auto self, int param1, int param2 ...) -> return_type {  code; });
template <typename Func>
decltype(auto) y_combinator(Func&& func) {
    return y_combinator_result<std::decay_t<Func>>{std::forward<Func>(func)};
}