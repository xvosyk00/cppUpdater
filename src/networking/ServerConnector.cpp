//
// Created by pavel on 11/24/22.
//

#include "ServerConnector.hpp"
#include <stdexcept>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

void hostname_to_ip(const char *hostname , char *ip)
{
  struct hostent *he;
  struct in_addr **addr_list;
  int i;
  if ( (he = gethostbyname( hostname ) ) == NULL)
  {
    herror("gethostbyname");
    throw std::runtime_error("gethostbyname failed.");
  }
  addr_list = (struct in_addr **) he->h_addr_list;
  for(i = 0; addr_list[i] != NULL; i++)
  {
    //Return the first one;
    strcpy(ip , inet_ntoa(*addr_list[i]) );
    return;
  }
  throw std::runtime_error("Address not found.");
}

std::unique_ptr<Connection> ServerConnector::connect(const std::string &hostname, int port) {
  if(connMock)
    return std::move(connMock);
  int sock, client_fd;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    throw std::runtime_error("Socket creation error.");
  }
  sockaddr_in serv_addr{};
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  char ip[20];
  hostname_to_ip(hostname.c_str(), ip);
  if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid address/ Address not supported.");
  }
  if ((client_fd  = ::connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
    throw std::runtime_error("Connection Failed.");
  }
  return std::make_unique<Connection>(sock);
}

void ServerConnector::setConnectionMock(std::unique_ptr<Connection> connection) {
  connMock = std::move(connection);
}
