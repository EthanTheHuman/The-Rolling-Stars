//
// (c) 2015 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

//Library Includes
#include <WS2tcpip.h>
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>


//Local Includes
#include "utils.h"
#include "network.h"
#include "consoletools.h"
#include "socket.h"


//Local Includes
#include "server.h"

CServer::CServer()
	:m_pcPacketData(0),
	m_pServerSocket(0)
{
	ZeroMemory(&m_ClientAddress, sizeof(m_ClientAddress));
}

CServer::~CServer()
{
	delete m_pConnectedClients;
	m_pConnectedClients = 0;

	delete m_pServerSocket;
	m_pServerSocket = 0;

	delete m_pWorkQueue;
	m_pWorkQueue = 0;

	delete[] m_pcPacketData;
	m_pcPacketData = 0;
}

bool CServer::Initialise()
{
	m_pcPacketData = new char[MAX_MESSAGE_LENGTH];

	//Create a work queue to distribute messages between the main  thread and the receive thread.
	m_pWorkQueue = new CWorkQueue<char*>();

	//Create a socket object
	m_pServerSocket = new CSocket();

	//Get the port number to bind the socket to
	unsigned short _usServerPort = DEFAULT_SERVER_PORT;

	//Initialise the socket to the local loop back address and port number
	if (!m_pServerSocket->Initialise(_usServerPort))
	{
		return false;
	}

	//Qs 2: Create the map to hold details of all connected clients
	m_pConnectedClients = new std::map < std::string, TClientDetails >();
	m_bOnline = true;
	return true;
}

bool CServer::AddClient(std::string _strClientName)
{
	//TO DO : Add the code to add a client to the map here...

	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		//Check to see that the client to be added does not already exist in the map, 
		if (it->first == ToString(m_ClientAddress))
		{
			return false;
		}
		//also check for the existence of the username
		else if (it->second.m_strName == _strClientName)
		{
			return false;
		}
	}
	//Add the client to the map.
	TClientDetails _clientToAdd;
	_clientToAdd.m_strName = _strClientName;
	_clientToAdd.m_ClientAddress = this->m_ClientAddress;

	std::string _strAddress = ToString(m_ClientAddress);
	m_pConnectedClients->insert(std::pair < std::string, TClientDetails >(_strAddress, _clientToAdd));
	return true;
}

bool CServer::SendData(char* _pcDataToSend)
{
	int _iBytesToSend = (int)strlen(_pcDataToSend) + 1;

	int iNumBytes = sendto(
		m_pServerSocket->GetSocketHandle(),				// socket to send through.
		_pcDataToSend,									// data to send
		_iBytesToSend,									// number of bytes to send
		0,												// flags
		reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet target
		sizeof(m_ClientAddress)							// size of the above address struct.
	);
	//iNumBytes;
	if (_iBytesToSend != iNumBytes)
	{
		std::cout << "There was an error in sending data from client to server" << std::endl;
		return false;
	}
	return true;
}

void CServer::ReceiveData(char* _pcBufferToReceiveData)
{
	struct timeval timeValue;
	int iSizeOfAdd = sizeof(m_ClientAddress);
	int _iNumOfBytesReceived;
	int _iPacketSize;

	
	//Make a thread local buffer to receive data into
	char _buffer[MAX_MESSAGE_LENGTH];

	while (m_bOnline)
	{
		timeValue.tv_sec = 15;
		timeValue.tv_usec = 0;
		setsockopt(m_pServerSocket->GetSocketHandle(), SOL_SOCKET, SO_RCVTIMEO,
			(char*)&timeValue, sizeof(timeValue));

		// pull off the packet(s) using recvfrom()
		_iNumOfBytesReceived = recvfrom(			// pulls a packet from a single source...
			m_pServerSocket->GetSocketHandle(),						// client-end socket being used to read from
			_buffer,							// incoming packet to be filled
			MAX_MESSAGE_LENGTH,					   // length of incoming packet to be filled
			0,										// flags
			reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet source
			&iSizeOfAdd								// size of the above address struct.
		);
		if (_iNumOfBytesReceived < 0)
		{
			int _iError = WSAGetLastError();
			//ErrorRoutines::PrintWSAErrorInfo(_iError);
			//return;
		}
		else
		{
			_iPacketSize = static_cast<int>(strlen(_buffer)) + 1;
			strcpy_s(_pcBufferToReceiveData, _iPacketSize, _buffer);
			char _IPAddress[100];
			inet_ntop(AF_INET, &m_ClientAddress.sin_addr, _IPAddress, sizeof(_IPAddress));

			std::cout << "Server Received \"" << _pcBufferToReceiveData << "\" from " <<
				_IPAddress << ":" << ntohs(m_ClientAddress.sin_port) << std::endl;
			//Push this packet data into the WorkQ
			m_pWorkQueue->push(_pcBufferToReceiveData);
		}
		//std::this_thread::yield();

	} //End of while (true)
	cout << "hello";
}

void CServer::GetRemoteIPAddress(char *_pcSendersIP)
{
	char _temp[MAX_ADDRESS_LENGTH];
	int _iAddressLength;
	inet_ntop(AF_INET, &(m_ClientAddress.sin_addr), _temp, sizeof(_temp));
	_iAddressLength = static_cast<int>(strlen(_temp)) + 1;
	strcpy_s(_pcSendersIP, _iAddressLength, _temp);
}

unsigned short CServer::GetRemotePort()
{
	return ntohs(m_ClientAddress.sin_port);
}

void CServer::ProcessData(char* _pcDataReceived)
{
	TPacket _packetRecvd, _packetToSend;
	_packetRecvd = _packetRecvd.Deserialize(_pcDataReceived);
	char c[30];
	switch (_packetRecvd.MessageType)
	{
	case HANDSHAKE:
	{
		std::cout << "Server received a handshake message " << std::endl;
		if (AddClient(ToString(m_ClientAddress)))
		{
			cout << "HandShake Successful" << endl;
			sockaddr_in TempAddress = m_ClientAddress;
			_packetToSend.Serialize(HANDSHAKE, "Handshake Successful");
			SendData(_packetToSend.PacketData);
			//broadcast to everyone
			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				if (it->first != ToString(TempAddress))
				{
					m_ClientAddress = it->second.m_ClientAddress;
					strcpy_s(c, ToString(TempAddress).c_str());
					_packetToSend.Serialize(LOBY, c);
					SendData(_packetToSend.PacketData);
				}
			}
			m_ClientAddress = TempAddress;
			//broadcast to client
			_packetToSend.Serialize(LOBY, "Host");
			SendData(_packetToSend.PacketData);
			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				strcpy_s(c, it->second.m_strName.c_str());
				_packetToSend.Serialize(LOBY, c);
				SendData(_packetToSend.PacketData);
			}
		}
		else
		{
			cout << "HandShake Failed" << endl;
			_packetToSend.Serialize(HANDSHAKE, "Handshake Failed");
			SendData(_packetToSend.PacketData);
		}
		break;
	}
	case DATA:
	{
		auto TempAddress = m_ClientAddress;
		for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
		{
			if (it->first == ToString(TempAddress))
			{
				for (auto It = m_pConnectedClients->begin(); It != m_pConnectedClients->end(); ++It)
				{
					std::string stringtemp = ToString(it->second.m_strName) + ">" + ToString(_packetRecvd.MessageContent);
					strcpy_s(c, stringtemp.c_str());
					_packetToSend.Serialize(DATA, c);
					m_ClientAddress = It->second.m_ClientAddress;
					SendData(_packetToSend.PacketData);
				}
			}
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		break;
	}
	case LOBY:
	{
		if (ToString(_packetRecvd.MessageContent) == ToString(" Ready")) {
			sockaddr_in TempAddress = m_ClientAddress;
			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				if (it->first != ToString(TempAddress))
				{
					m_ClientAddress = it->second.m_ClientAddress;
					strcpy_s(c, ToString(TempAddress).c_str());
					_packetToSend.Serialize(LOBY, c);
					SendData(_packetToSend.PacketData);
				}
			}
		}
	}
	case BROADCAST:
	{
		std::cout << "Received a broadcast packet" << std::endl;
		//Just send out a packet to the back to the client again which will have the server's IP and port in it's sender fields
		_packetToSend.Serialize(BROADCAST, "I'm here!");
		SendData(_packetToSend.PacketData);
		break;
	}

	default:
		break;

	}
}

CWorkQueue<char*>* CServer::GetWorkQueue()
{
	return m_pWorkQueue;
}

std::vector<std::string> CServer::RetrevePlayers()
{
	std::vector<std::string> temp;
	temp.push_back("Host");
	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		temp.push_back(it->second.m_strName);
	}
	return temp;
}
