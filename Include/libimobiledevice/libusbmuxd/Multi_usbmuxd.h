#ifndef LIBUSBMUXD_MULTI_USBMUXD_H_
#define LIBUSBMUXD_MULTI_USBMUXD_H_

#include <cstdint>
#include <cassert>
#include <string>
#include <vector>

#ifdef WIN32
#if (defined(_LIB)||defined(_DLL))
#define EXTERN_FUNC __declspec(dllexport)
#else
#define EXTERN_FUNC __declspec(dllimport)
#endif
#pragma comment(lib,"IPHLPAPI.lib")
#pragma comment(lib,"Shell32.lib")
#pragma comment(lib,"Ole32.lib")
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"Advapi32.lib")
#pragma comment(lib,"WinMM.lib")
#pragma comment(lib,"Psapi.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Winhttp.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"libplist.lib")
#pragma comment(lib,"libxml2.lib")
#pragma comment(lib,"libiconv.lib")
#pragma comment(lib,"libcnary.lib")
#else
#define EXTERN_FUNC
#endif

#if defined(WIN32) || defined(__CYGWIN__)
void SetGlobalLocalListenPort(const std::uint32_t tcp_port);
#else
void SetGlobalLinuxListenPath(const char* socket_path);
#endif

namespace usbmuxd{
  class UsbmuxdDevice
  {
  public:
    UsbmuxdDevice();
    void SetUdid(const char* udid);
    void SetLocalPort(std::uint32_t local_port);
    void SetRemotePort(std::uint32_t remote_port);
    void SetLinuxSocketPath(const char* socket_path);
    void SetLinuxSocketPathLockFile(const char* socket_path_lock_file);
    void SetHandle(int handle);
    void SetProductId(int product_id);
    void SetSockSFD(int sock_sfd);
    bool SetUsbmuxdDeviceinfo();
    void Release();
    bool IsOK();
    std::string udid() const{
      return udid_;
    }
    std::uint32_t local_port() const{
      return local_port_;
    }
    std::uint32_t remote_port() const{
      return remote_port_;
    }
    std::string unix_socket_path() const {
      return unix_socket_path_;
    }
    std::string unix_socket_path_lockfile() const {
      return unix_socket_path_lockfile_;
    }
    int sock_sfd() const{
      return sock_sfd_;
    }
  private:
    std::string udid_;
    std::uint32_t local_port_;
    std::uint32_t remote_port_;
    std::string unix_socket_path_;
    std::string unix_socket_path_lockfile_;
    int handle_;
    int product_id_;
    int sock_sfd_;
    void* usbmuxd_device_info_t_dummy_;
  };
  class UsbmuxdRW
  {
  public:
    EXTERN_FUNC int Write(const char *data, std::uint32_t len, std::uint32_t *sent_bytes);
    EXTERN_FUNC int ReadTimeout(char *data, uint32_t len, uint32_t *recv_bytes, unsigned int timeout);
    EXTERN_FUNC int Read(char *data, uint32_t len, uint32_t *recv_bytes);
    EXTERN_FUNC void SetSFD(std::uint32_t sfd){
      sfd_ = sfd;
    }
    EXTERN_FUNC std::uint32_t sfd() const{
      return sfd_;
    }
  private:
    std::uint32_t sfd_;
  };
  class Multi_usbmuxd
  {
  public:
    enum class ActivationStatusTable{ kOK, kFail };
    EXTERN_FUNC Multi_usbmuxd();
    EXTERN_FUNC ~Multi_usbmuxd();
    EXTERN_FUNC bool AddDevice(const char* udid, const std::uint32_t local_port, const std::uint32_t remote_port);
    EXTERN_FUNC bool AddLinuxDevice(const char* udid, const char* socket_path, const std::uint32_t remote_port);
    EXTERN_FUNC bool ActivationDevice(const char* udid);
    EXTERN_FUNC ActivationStatusTable ActivationStatus(const char* udid);
    EXTERN_FUNC bool DeactivationDevice(const char* udid);
    EXTERN_FUNC bool GetUsbmuxdRW(const char* udid, UsbmuxdRW& usbmuxd_rw);
  private:
    std::vector<UsbmuxdDevice*> connection_info_;
  };
}

#endif