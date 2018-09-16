#include <boost/program_options.hpp>
#include <iostream>

using namespace boost::program_options;

void on_age(int age)
{
    std::cout << "On age: " << age << std::endl;
}

int main(int argc, const char *argv[])
{
    try {
        options_description desc{"Options"};
        desc.add_options()
            ("Help, h", "Help screen")
            ("pi", value<float>()->default_value(3.14f), "Pi")
            ("age", value<int>()->notifier(on_age), "Age");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("Help"))
            std::cout << desc << std::endl;
        else if (vm.count("age"))
            std::cout << "Age: " << vm["age"].as<int>() << std::endl;
        else if (vm.count("pi"))
            std::cout << "Pi: " << vm["pi"].as<float>() << std::endl;
    }
    catch (const error &ex) {
        std::cerr << ex.what () << std::endl;
    }
}
