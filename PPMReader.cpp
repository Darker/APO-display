#include "PPMReader.h"
PPMReader::PPMReader(const char* filename) {
    file.open(filename);
    std::string bleh;
    if(isValid()) {
        file>>bleh;
        std::cout<<"Magic number: "<<bleh<<std::endl;
        file.get();
        char buffer[40];
        std::cout<<"Next character: "<<(char)file.peek()<<std::endl;
        while(file.peek()=='#') {
            file.getline(buffer, 40);
            std::cout<<"Ignoring comment: "<<buffer<<std::endl;
        }
        file>>width>>height;
        std::cout<<"Dimensions: "<<width<<"x"<<height<<std::endl;
        int ignored = -1;
        file>>ignored;
        std::cout<<"Max brightness: "<<ignored<<std::endl;
        // Ignore newline, if any
        if(file.peek()=='\n')
            file.get();
        // remember start offset
        startOfData = file.tellg();
        std::cout<<"Data starts at byte offset "<<startOfData<<std::endl;
    }
}
Color PPMReader::nextColor() {
    if(isValid()) {
        if(/*file.eof()*/file.peek() == EOF) {
            file.seekg(startOfData);
            std::cout<<"Overflow in the file.";
        }
        Color c(file.get(), file.get(), file.get());
        //file>>c.r>>c.g>>c.b;
        if(((int)file.tellg())-10<startOfData)
            std::cout<<"Reading color: "<<(std::string)c<<'\n';
        return c;
    }
//std::cout<<"dfdsgdf\n";
    return Color(0,0,0);
}
void PPMReader::reset() {
    file.seekg(startOfData);
    std::cout<<"Reset to: "<<startOfData<<std::endl;
}
