# Telegram Bot API C++
Handy Telegram bot API wrapper. **IN DEVELOPMENT**.

## Status
- Current status: **In Development**
- Version: __0.1a__
- Depencencies: 
  - [libcurl](https://www.github.com/curl/curl)(install with [this guide](https://curl.haxx.se/docs/install.html))
  - [nlohmann/json](https://www.github.com/nlohmann/json)(1 .hpp file. Easy to remove this dep)
- Realized bot features: *polling*, *callbacks*

## Realised API methods:
|Method name|Status|Overloads|Note|
|---|---|---|---|
|sendMessage|Good|+7|`Message` is not finished yet|
|forwardMessage|Good|+7|☝️|
|sendPhoto|Raw|+1|`PhotoSize` is not realized yet|
|sendAudio|Raw|+1|`Audio` is not realized yet|
|sendDocument|Raw|+1|`Document` is not realized yet|
|sendVideo|Raw|+1|`Video` is not realized yet|
|sendVoice|Raw|+1|`Voice` is not realized yet|
|sendVideoNote|TODO||`VideoNote` is not realized yet|
|sendMediaGroup|TODO|||
|sendLocation|TODO||`Location` is not realized yet|
|editMessageLiveLocation|TODO||☝️|
|stopMessageLiveLocation|TODO||☝️|
|sendVenue|Not exists||`Venue` is not realized yet|
|sendContact|Good|+11|`Contact` is not realized yet
|sendChatAction|Good|+1|No constants for chat actions|
|getUserProfilePhotos|Good|+2|`UserProfilePhotos` is not realized yet|
|getFile|Good||`File` is not realized yet|
|kickChatMember|Nice|+3|*TODO: add easy ban for mins/hours/days*|
|unbanChatMember|Done|+1||
|restrictChatMember|Nice|+7|*TODO: add easy ban for mins/hours/days*|
|**Nothing else yet**|**...**|**...**|**TODO next methods**|

## Realized API object types:
|Type|Status|Note|
|---|---|---|
|User|Done||
|Chat|Good|Problem with destructor + constructor|
|Message|Raw|A lot of *TODO* there|
|PhotoSize|Nice|**TODO: tests**|
|**Empty or nonexistent types**|**...**|**TODO next types**|

## TODO list:
- Realize and finish off more methods
- Realize and finish off more types
- More tools + WebHook
- Multithreading + Async
- Own exceptions
- Shield with namespace
- **...**