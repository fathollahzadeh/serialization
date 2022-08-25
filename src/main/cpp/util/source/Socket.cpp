#include "Socket.h"

Socket::Socket() {
    mSocket = -1;
    memset(&mAddr, 0, sizeof(mAddr));
}

Socket::~Socket() {
    if (isValid())
        close(mSocket);
}

bool Socket::create() {
    mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (!isValid())
        return false;

//    // TIME_WAIT - argh
//    int on = 1;
//    if (setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on)) == -1)
//        return false;
    return true;
}

bool Socket::bind(int port) {
    if (!isValid()) {
        return false;
    }
    bzero((char *) &mAddr, sizeof(mAddr));
    mAddr.sin_family = AF_INET;
    mAddr.sin_addr.s_addr = INADDR_ANY;
    mAddr.sin_port = htons(port);

    int bindReturn = ::bind(mSocket, (struct sockaddr *) &mAddr, sizeof(mAddr));

    if (bindReturn == -1) {
        return false;
    }

    return true;
}

//int sockfd, newsockfd, portno;
//     socklen_t clilen;
//     char buffer[256];
//     struct sockaddr_in serv_addr, cli_addr;
//     int n;
//     if (argc < 2) {
//         fprintf(stderr,"ERROR, no port provided\n");
//         exit(1);
//     }
//     sockfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (sockfd < 0)
//        error("ERROR opening socket");
//     bzero((char *) &serv_addr, sizeof(serv_addr));
//     portno = atoi(argv[1]);
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_addr.s_addr = INADDR_ANY;
//     serv_addr.sin_port = htons(portno);
//     if (bind(sockfd, (struct sockaddr *) &serv_addr,
//              sizeof(serv_addr)) < 0)
//              error("ERROR on binding");
//     listen(sockfd,5);
//     clilen = sizeof(cli_addr);
//     newsockfd = accept(sockfd,
//                 (struct sockaddr *) &cli_addr,
//                 &clilen);
//     if (newsockfd < 0)
//          error("ERROR on accept");
//     bzero(buffer,256);
//     n = read(newsockfd,buffer,255);
//     if (n < 0) error("ERROR reading from socket");
//     printf("Here is the message: %s\n",buffer);
//     n = write(newsockfd,"I got your message",18);
//     if (n < 0) error("ERROR writing to socket");
//     close(newsockfd);
//     close(sockfd);
//     return 0;

bool Socket::accept(Socket *newSocket) const {
    int addrLength = sizeof(mAddr);
    newSocket->mSocket = ::accept(mSocket, (sockaddr * ) & mAddr, (socklen_t * ) & addrLength);
    if (newSocket->mSocket <= 0)
        return false;
    else
        return true;
}

bool Socket::listen(int count) const {
    if (!isValid()) {
        return false;
    }
    int listenReturn = ::listen(mSocket, count);
    if (listenReturn == -1) {
        return false;
    }
    return true;
}

bool Socket::connect(const string& ip, int port) {
    if (!isValid()) return false;
    struct hostent *host;
    host = gethostbyname(ip.c_str());
    if (host == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        return false;
    }
    bzero((char *) &mAddr, sizeof(mAddr));
    mAddr.sin_family = AF_INET;
    bcopy((char *)host->h_addr, (char *)&mAddr.sin_addr.s_addr, host->h_length);
    mAddr.sin_port = htons(port);
    int status = ::connect(mSocket, (struct sockaddr *) &mAddr,sizeof(mAddr));
    if (status == 0)
        return true;
    else
        return false;
}

//int sockfd, portno, n;
//    struct sockaddr_in serv_addr;
//    struct hostent *server;
//
//    char buffer[256];
//    if (argc < 3) {
//       fprintf(stderr,"usage %s hostname port\n", argv[0]);
//       exit(0);
//    }
//    portno = atoi(argv[2]);
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd < 0)
//        error("ERROR opening socket");
//    server = gethostbyname(argv[1]);
//    if (server == NULL) {
//        fprintf(stderr,"ERROR, no such host\n");
//        exit(0);
//    }
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    bcopy((char *)server->h_addr,
//         (char *)&serv_addr.sin_addr.s_addr,
//         server->h_length);
//    serv_addr.sin_port = htons(portno);
//    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
//        error("ERROR connecting");
//    printf("Please enter the message: ");
//    bzero(buffer,256);
//    fgets(buffer,255,stdin);
//    n = write(sockfd,buffer,strlen(buffer));
//    if (n < 0)
//         error("ERROR writing to socket");
//    bzero(buffer,256);
//    n = read(sockfd,buffer,255);
//    if (n < 0)
//         error("ERROR reading from socket");
//    printf("%s\n",buffer);
//    close(sockfd);
//    return 0;


void Socket::write(char *buffer, long contentSize) {
    //New Code:
    long bytesWritten = 0;
    long status = 0;
    while (bytesWritten < contentSize) {
        status = ::write(mSocket, buffer + bytesWritten, contentSize - bytesWritten);
        bytesWritten += status;

        //Error Handling:
        if (!status)
            throw std::runtime_error("Could not write to socket.");;
    }
    if (bytesWritten != contentSize)
        throw std::runtime_error("ClientSocket: Mismatch in write()");

}

void Socket::read(char *buffer, long contentSize) {
    //New Code:
    long bytesRead = 0;
    long status = 0;
    while (bytesRead < contentSize) {
        status = ::read(mSocket, buffer + bytesRead, contentSize - bytesRead);
        bytesRead += status;

        //Error Handling:
        if (!status)
            throw std::runtime_error("Could not read from socket.");
    }
    if (bytesRead != contentSize) {
        throw std::runtime_error("ClientSocket: Mismatch in read()");
    }
}

bool Socket::isValid() const {
    return mSocket != -1;;
}


bool Socket::readACK() {
    char *ack = new char[1];
    read(ack, 1);
    if (ack[0] != '1') {
        throw std::runtime_error("Can't read correct ACK from socket !");
    }
    return true;
}

bool Socket::writeACK() {
    char *ack = new char[1];
    ack[0] = '1';
    write(ack, 1);
    return true;
}

void Socket::write(int value) {
    char *buf = new char[sizeof(value)];
    memcpy(buf, &value, sizeof(value));
    write(buf, sizeof(value));
}

int Socket::readInt() {
    char *val = new char[sizeof(int)];
    read(val, sizeof(int));
    int intVal;
    memcpy(&intVal, val, sizeof(intVal));
    return intVal;
}
