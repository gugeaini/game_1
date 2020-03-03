#include<iostream>
#include<zinx.h>

using namespace std;

//2-写功能函数类
class Echo :public AZinxHandler
{
	// 通过 AZinxHandler 继承
	virtual IZinxMsg* InternelHandle(IZinxMsg& _oInput) override
	{
		//回显到标准输出
		GET_REF2DATA(BytesMsg, input, _oInput);

		cout << input.szData << endl;
		return nullptr;
	}
	virtual AZinxHandler* GetNextHandler(IZinxMsg& _oNextMsg) override
	{
		//下一个处理
		return nullptr;
	}
}*poEcho=new Echo();

//3-写通道类
class TextStdin :public Ichannel
{
	// 通过 Ichannel 继承
	virtual bool Init() override
	{
		return true;
	}
	virtual bool ReadFd(std::string& _input) override
	{
		cin >> _input;
		return true;
	}
	virtual bool WriteFd(std::string& _output) override
	{
		return false;
	}
	virtual void Fini() override
	{
	}
	virtual int GetFd() override
	{
		return 0;
	}
	virtual std::string GetChannelInfo() override
	{
		return "stdin";
	}
	virtual AZinxHandler* GetInputNextStage(BytesMsg& _oInput) override
	{
		return poEcho;
	}
};


int main()
{
	//1-初始化框架
	ZinxKernel::ZinxKernelInit();

	//4-将通道对象添加到框架
	TextStdin* poStdin = new TextStdin();
	ZinxKernel::Zinx_Add_Channel(*poStdin);

	//5-运行框架
	ZinxKernel::Zinx_Run();

	//释放框架
	ZinxKernel::ZinxKernelFini();

	return 0;
}