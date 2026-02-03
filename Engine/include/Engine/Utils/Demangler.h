const std::string demangle(std::string& i_input) {
    const std::string prefix = "class ";
    if (i_input.rfind(prefix, 0) == 0) { // vérifie si "class " est au début
        i_input = i_input.substr(prefix.size()); // supprime "class "
    }
    return i_input;
}