FROM lganzzzo/ubuntu-cmake-libressl:latest

RUN apk add postgresql-dev

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 8000 8000

ENTRYPOINT ["./example-postgresql-exe"]
