#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

class Doc
{
private:
	std::string					fileName;
	std::vector<std::string>	extraFiles;
	std::string					className;
	std::vector<std::string>	methodTests;
public:
	Doc(std::string file_name, char *extra_files[]){
		for (int i = 0; extra_files[i]; i++){
			this->extraFiles.push_back(extra_files[i]);
		}
		this->fileName = file_name;
	}
	~Doc(){

	}

	void	run(){
		findClassName();
		findMethodTests();
		createMainTemplate();
		compileMainTemplate();
		executeMainTemplate();
		removeTemps();
		/* std::cout << this->className << "\n";
		for (auto i : this->methodTests){
			std::cout << i << "\n";
		} */
	}

	void	findClassName(){
		std::fstream	file;
	
		file.open(fileName.c_str());
		std::string line;
		std::size_t index;
		while (getline(file, line)){
			index = line.find("class");
			if (index < 100000000)
			{
				int i;
				for (i = index + 5; isspace(line[i]); i++)
					;
				for (; !(isspace(line[i])) && i < line.size(); i++)
					;
				line[i] = '\0';
				this->className = line.c_str() + index + 5;
				this->removeSpaces(this->className);
				break ;
			}
		}
	}
	void	findMethodTests(){
		std::fstream	file;
		file.open(fileName.c_str());
		std::string line;
		std::size_t index;
		while (getline(file, line)){
			index = line.find("test_");
			if (index < 100000000)
			{
				int i;
				for (i = index; line[i] != '(' && i < line.size(); i++)
					;
				line[i] = '\0';
				this->methodTests.push_back(line.c_str() + index);
				this->removeSpaces(this->methodTests.back());
			}
		}
	}

	void	createMainTemplate(){
		std::fstream	mainTemplate;

		mainTemplate.open("doc_tmp_main_template.cpp", std::ios_base::out);
		mainTemplate << "#include \"" << this->fileName << "\"" << std::endl;
		mainTemplate << "int main(){" << std::endl;
		mainTemplate << "\t" << this->className << " tmp;" << std::endl;
		for (std::vector<std::string>::iterator i = this->methodTests.begin(); i != this->methodTests.end(); i++){
			mainTemplate << "\t" << "tmp." << *i << "();" << std::endl;
		}
		mainTemplate << "}" << std::endl;
	}



	void	removeSpaces(std::string &str){
		for (int i = 0; i < str.size(); i++){
			if (isspace(str[i]))
				str.erase(i, 1);
		}
	}

	void executeMainTemplate(){
		int pid = fork();
		if (pid == 0)
		{
			char *argv[1] = {NULL};
			std::cout << execv("./doc_tmp_main_template", argv);
		}
		wait(NULL);
	}

	void compileMainTemplate(){
		int pid = fork();

		if (pid == 0)
		{
			char **argv = new char*[5 + this->extraFiles.size()];
			for (int i = 0; i < 4 + this->extraFiles.size(); i ++)
				argv[i] = new char[1024]; 
			strcpy(argv[0], "c++");
			strcpy(argv[1], "doc_tmp_main_template.cpp");
			int index = 2;
			for (std::vector<std::string>::iterator iterator = this->extraFiles.begin(); iterator != this->extraFiles.end(); iterator++){
				strcpy(argv[index], iterator->c_str());
				index++;
			}
			strcpy(argv[index], "-o");
			strcpy(argv[++index], "doc_tmp_main_template");
			argv[++index] = NULL;
			std::cout << execv("/usr/bin/c++", argv);
		}
		wait(NULL);
		
	}

	void removeTemps(){
		remove("doc_tmp_main_template.cpp");
		remove("doc_tmp_main_template");
	}
};


int main(int argc, char *argv[]){
	if (argc < 2)
		return 0;
	Doc doc(argv[1], &argv[2]);
	doc.run();
}