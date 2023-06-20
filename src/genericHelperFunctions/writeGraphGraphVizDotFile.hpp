/////////////////////////////////////////////////////////////
// Title  : testGraphProperties.cpp                        //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Build graphs and test properties of graphs.    //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////





/**
 * @brief Updates a text file with additional content.
 *
 * This function reads the content of the input file, inserts new text at a specific line,
 * and writes the updated content to a new output file. The new file name is derived by
 * appending "Updated" to the original file name. The input file should exist and be accessible.
 *
 * @param inputPath The path to the input file.
 * @return The path to the updated output file.
 */
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







/**
 * @brief Prints a graph to a file using Graphviz.
 *
 * This function writes a Boost undirected graph to a Graphviz DOT file. It then converts
 * the DOT file to the specified output format (e.g., PNG, SVG) using the Graphviz "dot" command.
 * The resulting file is saved in the specified directory with the given graph name.
 *
 * @param graph The undirected graph to print.
 * @param fileDir The directory where the output file will be saved.
 * @param graphName The name of the output file without the file extension.
 * @param format The desired output format ("png", "svg", or any other format to generate both).
 */
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

    