//
// Created by bretzel on 20-04-18.
//

#include <Lsc/AppBook/AppBook.h>
#include <map>


namespace Lsc
{


/*
 *
 *
 
App &App::Init()
{
    if(!App::mStaticInstance->mComponentData.empty()) return *App::mStaticInstance;
    App& Book = *App::mStaticInstance;
    
    App::mStaticInstance->mComponentData = {
        {TextCtl::Reset   ,"\033[0m"},
//        {TextCtl::Italic  ,""},
        {TextCtl::Sup     ,"<sup>"},
        {TextCtl::Sub     ,"</sup>"},
        {TextCtl::Code    ,"<code>"},
        {TextCtl::EndCode ,"</code>"},
//        {TextCtl::Pre     ,""},
//        {TextCtl::EndPre  ,""},
        {TextCtl::Eol     ,"\n"}
    };
    App::mStaticInstance->mText
    << App::mStaticInstance->mConfig.Title
    << App::mStaticInstance->mComponentData[TextCtl::Eol];
    
    if(!Book.mConfig.Path.empty())
    {
        // Not yet ready to output to the given file.
        Book.mFile = &std::cout; // It's that simple!!
    }
    else
        Book.mFile = &std::cout; // It's that simple!!
        
    // Continue init...
    
    return *App::mStaticInstance;
}

App::ConfigData &App::Config()
{
    if(!App::mStaticInstance)
        App::mStaticInstance = new App;
    
    return App::mStaticInstance->mConfig;
}

App::Log &App::Begin(App::Prefix Prefix_)
{
    Log::Shared L = std::make_shared<App::Log>(nullptr, App::Prefix::Debug);
    if(App::mStaticInstance->mCurrentLog)
    {
        L->SetParent(App::mStaticInstance->mCurrentLog);
        App::mStaticInstance->mCurrentLog->SetChild(L);
    }
    
    App::mStaticInstance->mCurrentLog = L;
    (*L) << Prefix_ << ':';
    //...
    return *L;
}


std::string App::ToStr(App::Prefix Prefix_)
{
    std::map<App::Prefix, std::string> _ = {
        {App:: Debug    ,"\x1b[38;5;245m➤ Debug\x1b[0m"},
        {App:: Info     ,"\x1b[38;5;68m⚫ Info\x1b[0m"},
        {App:: Error    ,"\x1b[38;5;52m✘ Error\x1b[0m"},
        {App:: Warning  ,"\x1b[38;5;100m⚠ Warning\x1b[0m"},
        {App:: Exception,"\x1b[38;5;177m⚡ Exception\x1b[0m"},
        {App:: Fatal    ,"\x1b[38;5;52m☠ Fatal\x1b[0m"},
        {App:: Success  ,"\x1b[38;5;46m✔ Success\x1b[0m"},
        {App:: Notice   ,"\x1b[38;5;71m✎ Notice\x1b[0m"}
    };
    return _[Prefix_];
}



void App::End(std::function<void(const std::string &)> EndFN)
{
    App::Instance().mText << App::Instance().mCurrentLog->mText;
    if(EndFN)
        EndFN(App::Instance().mText());
    
    
    delete mStaticInstance;
}

std::string App::Text()
{
    return App::Instance().mText();
}


std::string App::Icon(App::Prefix Prefix_)
{
    ///@note This is a quick pre-coding test...
    std::map<App::Prefix, std::string > mIcons = {
        {App::Debug    ,"\x1b[38;5;245m➤ "},
        {App::Info     ,"\x1b[38;5;68m⚫ "},
        {App::Error    ,"\x1b[38;5;52m✘ "},
        {App::Warning  ,"\x1b[38;5;100m⚠ "},
        {App::Exception,"\x1b[38;5;177m⚡ "},
        {App::Fatal    ,"\x1b[38;5;52m☠ "},
        {App::Success  ,"\x1b[38;5;46m✔ "},
        {App::Notice   ,"\x1b[38;5;71m✎ "}
    };
    return mIcons[Prefix_];
}


App::Log &App::Create(std::string Name_)
{
    return *std::make_shared<App::Log>(App::mStaticInstance->mCurrentLog, App::Prefix::Debug);
}

App::Log &App::Log::operator<<(App::Prefix Prefix_)
{
    mText << "%-30s" << App::ToStr(Prefix_);
    return *this;
}


App::Log &App::Log::operator<<(Lsc::TextCtl C)
{
    mText << App::Instance().mComponentData[C];
    mNewLine = C == TextCtl::Eol;
    return *this;
}


App::Log::~Log()
{
    std::cout << __PRETTY_FUNCTION__ << " ⚒ \\O/\n";
    mText.Clear();
//    delete mChild;
}

App::Log::Log(App::Prefix Prefix_):mPrefix(Prefix_){}

App::Log::Log(App::Log::Shared Parent_, App::Prefix Prefix_):
    mParent(Parent_),
    mPrefix(Prefix_)
{}





void App::Log::SetChild(App::Log::Shared Child_)
{
    if(!Child_) return;
    mChild = Child_;
    mChild->mIndent = mIndent + 4; // Hard coded indent for now -> Will get Indent value from the App::Config Data
}


void App::Log::End()
{
    if(mChild)
        mText << mChild->mText;
}

App::Log &App::Log::operator<<(Lsc::Color C)
{
    mText <<  "\x1b[38;5;%3dm" << static_cast<int>(C);
    return *this;
}
std::string App::Log::Endl()
{
    return App::mStaticInstance->mComponentData[TextCtl::Eol];
}


void App::Log::SetParent(App::Log::Shared Parent_)
{
    mParent = Parent_;
}

}
*/
}
