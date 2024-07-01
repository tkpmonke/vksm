#include "vksm.h"
#include "shaderc/shaderc.hpp"

bool verbose;

void vksmInterpretShaderFile(const char* location)
{
   std::string includeInAll;
   std::string contents;
   std::string vertex;
   std::string fragment;
   std::string name = "hey";
   int vertLocation;
   int fragLocation;
   int vertEndLocation;
   int fragEndLocation;

   std::ifstream file(location);

   std::stringstream s;
   s << file.rdbuf();
   contents = s.str();

   if (!file.is_open())
   {
      printf("File Doesn't Exist\n");
      exit(1);
   }
   
   vertLocation = contents.find(VKSM_VERTEX_DEFINITION_TOKEN); 
   fragLocation = contents.find(VKSM_FRAGMENT_DEFINITION_TOKEN);
   vertEndLocation = contents.find(VKSM_SHADER_END_TOKEN) - 18;
   fragEndLocation = contents.find(VKSM_SHADER_END_TOKEN, vertEndLocation);
   includeInAll = contents.substr(0, vertLocation);
   vertex = includeInAll + "\n" + contents.substr(vertLocation+VKSM_VERTEX_DEFINITION_TOKEN.size(), vertEndLocation); 
   fragment = includeInAll + "\n" + contents.substr(fragLocation+VKSM_FRAGMENT_DEFINITION_TOKEN.size(), contents.size()-1);
   
   fragment.at(fragment.size()-1) = ' ';
   if (verbose)
   {
      std::cout << "## WHATS BEING INCLUDED IN BOTH SHADERS ##\n" << includeInAll << "\n";
      std::cout << "## VERTEX ##\n" << vertex << "\n";
      std::cout << "## FRAGMENT ##\n" << fragment << "\n";
   }
   
   vksmCompile(vertex, fragment, name);
}

void vksmCompile(std::string vert, std::string frag, std::string name)
{
   /*std::filesystem::create_directory("./temp");
   
   std::ofstream vf("./temp/vert.vert");
   vf << vert;
   std::ofstream ff("./temp/frag.frag");
   ff << frag;

   std::string vertCommand = "glslc -std=450core ./temp/vert.vert -o " + name + std::string(".vert.spv");
   system(vertCommand.data());

   std::string fragCommand = std::string("glslc -std=450core ./temp/frag.frag -o ") + name + std::string(".frag.spv"); 
   
   system(fragCommand.data());

   std::system("rm ./temp -r");
   
   if (verbose)
   {
      std::cout << "\n" << (std::string("glslc ./temp/vert.vert -o ") + name + std::string(".vert.spv")).data() << "\n";
      std::cout << "\n" << std::string("glslc ./temp/frag.frag -o ") + name + std::string(".frag.spv") << "\n";
   }*/
   shaderc::Compiler compiler;
   shaderc::CompileOptions options;

   options.AddMacroDefinition("MADE_WITH_VULKAN_SHADER_MIXER_AND_LOVE", ":heart:");
   shaderc::PreprocessedSourceCompilationResult result = compiler.PreprocessGlsl(vert, shaderc_glsl_vertex_shader, name.data(), options);
   shaderc::PreprocessedSourceCompilationResult resultf = compiler.PreprocessGlsl(frag, shaderc_glsl_fragment_shader, name.data(), options);

   if (result.GetCompilationStatus() != shaderc_compilation_status_success)
      std::cerr << result.GetErrorMessage();
 
   if (resultf.GetCompilationStatus() != shaderc_compilation_status_success)
      std::cerr << resultf.GetErrorMessage();
   options.SetOptimizationLevel(shaderc_optimization_level_size);

   shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(vert, shaderc_glsl_vertex_shader, name.data(), options);
   shaderc::SpvCompilationResult modulef = compiler.CompileGlslToSpv(frag, shaderc_glsl_fragment_shader, name.data(), options);
  
   if (module.GetCompilationStatus() != shaderc_compilation_status_success)
      std::cerr << module.GetErrorMessage();
   if (modulef.GetCompilationStatus() != shaderc_compilation_status_success)
      std::cerr << modulef.GetErrorMessage();
   
   std::vector<uint32_t> m = {module.cbegin(), module.cend()}; 
   std::ofstream o(name+std::string("_vert.spv"));
   for (int i = 0; i < m.size(); ++i)
   {
      o << static_cast<unsigned char>(m[i] & 0x000000FF);
   }

   m = {modulef.cbegin(), modulef.cend()};
   o = std::ofstream(name+std::string("_frag.spv"));
   for (int i = 0; i < m.size(); ++i)
   {
      o << static_cast<unsigned char>(m[i] & 0x000000FF);
   }
}

int main(int argc, char* argv[])
{
   for (int i = 0; i < argc; i++)
   {
      if (strcmp(argv[i], "-f") == 0)
      {
         
         printf("Opening File %s\n", argv[i+1]);
         vksmInterpretShaderFile(argv[i+1]);
      }
      
      if (strcmp(argv[i], "-v") == 0)
      {
         verbose = true;
      }
   }
}
