#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <functional>
#include <string>
#include <unordered_map>

class HttpRequest;
class HttpResponse;

class FileHandler
{
public:
	FileHandler();
	~FileHandler();
	
	// 设置映射路径
	void SetPrefixPath(std::string path) { prefix_path_ = path; }

	// 获取处理函数
	std::function<void(const HttpRequest&, std::unordered_map<std::string, std::string>&, HttpResponse* response)> GetHandler()
	{
		return std::bind(&FileHandler::Handler, this, std::placeholder::_1, std::placeholder::_2, std::placeholder::_3);
	}
private:
	// 处理对于静态文件的访问
	void Handler(const HttpRequest& request, std::unordered_map<std::string, std::string>& match_map, HttpResponse* response);

	// 映射的文件目录路径
	std::string prefix_path_;
};

#endif // FILEHANDLER_H