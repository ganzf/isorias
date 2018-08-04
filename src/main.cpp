# include "fengin-core/include/FenginCore.hpp"
# include "Systems/Splashscreen.hpp"
# include "json/Json.hpp"

int main(int, char **av)
{
    fengin::FenginCore core(av[0]);
    orias::utils::Json config("./config.json");
    auto const &dependencies = config["dependencies"];

    fengin::StartParameters params;
    params.logWhenLoading = dependencies["logWhenLoading"].asBool();
    params.recursive = dependencies["recursiveLoading"].asBool();
    params.configFilePath = dependencies["directory"].asString();

    if (core.start(params) != 0)
        return 1;
    core.addSystem<orias::scenes::Splashscreen>(config);
    core.run();
    return 0;
}
