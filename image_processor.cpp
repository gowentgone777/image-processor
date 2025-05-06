#include "image.h"
#include "parser.h"

int main(int argc, const char** argv) {
    Parser parsed(argc, argv);
    parsed.Parse();
    Image image;
    image.Read(parsed.GetFileForReading());
    for (auto& filter : parsed.GetFilters()) {
        image = filter->Apply(image);
    }
    image.Save(parsed.GetFileForWriting());
}
