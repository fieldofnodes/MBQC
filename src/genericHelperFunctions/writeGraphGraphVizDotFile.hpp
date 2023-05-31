/////////////////////////////////////////////////////////////
// Title  : testGraphProperties.cpp                        //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Build graphs and test properties of graphs.    //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////


typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;



std::string updateTextFile(std::string inputPath){
    std::ifstream infile(inputPath);
    std::size_t pos = inputPath.find_last_of(".");
    std::string outputPath;
    if (pos != std::string::npos) {
        std::string prefix = inputPath.substr(0, pos);
        std::string suffix = inputPath.substr(pos);
        outputPath = prefix + "Updated" + suffix;
    }

    std::ofstream outfile(outputPath);

    // Read and write the first line
    std::string line;
    std::getline(infile, line);
    outfile << line << std::endl;

    // Insert new text at line 2
    outfile << "graph [layout = neato]" << std::endl;
    outfile << "node [shape = circle," << std::endl;
    outfile << "style = filled," << std::endl;
    outfile << "style = filled," << std::endl;
    outfile << "color = lightblue]" << std::endl;
    outfile << "edge [color = silver]" << std::endl;
    
    // Write the remaining lines
    while (std::getline(infile, line)) {
        outfile << line << std::endl;
    }

    // Close the files
    infile.close();
    outfile.close();
    
    return outputPath;
}




void printGraphToFile(const undirectedGraph& graph,std::string fileDir,std::string graphName,std::string format){
    // Create a Graphviz output stream
    std::stringstream outputFile;
    outputFile << fileDir << "/" << graphName;
    

    std::ofstream dot_file(outputFile.str()+".dot");
    

    
    // Write to file
    boost::write_graphviz(
        dot_file, 
        graph);
    
    std::string updatedDotFile = updateTextFile(outputFile.str()+".dot");


    if(format == "png"){
        // Convert the DOT file to PNG
        std::stringstream dotPath; 
        std::stringstream pngPath;
        std::stringstream sysString;
        dotPath << outputFile.str() << ".dot";
        pngPath << outputFile.str() << ".png";
        sysString << "dot -Tpng " << updatedDotFile << " -o " << pngPath.str();
        std::system(sysString.str().c_str());

    } else if (format == "svg"){
        // Convert the DOT file to SVG
        std::stringstream dotPath; 
        std::stringstream svgPath;
        std::stringstream sysString;
        dotPath << outputFile.str() << ".dot";
        svgPath << outputFile.str() << ".svg";
        sysString << "dot -Tpng " << updatedDotFile << " -o " << svgPath.str();
        std::system(sysString.str().c_str());
    } else {
        // Convert the DOT file to PNG and SVG
        std::stringstream dotPath; 
        std::stringstream pngPath;
        std::stringstream svgPath;
        std::stringstream pngSysString;
        std::stringstream svgSysString;
        dotPath << outputFile.str() << ".dot";
        pngPath << outputFile.str() << ".png";
        svgPath << outputFile.str() << ".svg";
        pngSysString << "dot -Tpng " << updatedDotFile << " -o " << pngPath.str();
        svgSysString << "dot -Tpng " << updatedDotFile << " -o " << svgPath.str();
        std::system(pngSysString.str().c_str());
        std::system(svgSysString.str().c_str());
    }
}

    