FROM ubuntu:latest
LABEL maintainer="Mathieu GAILLARD"

RUN apt update && \
    apt install -y curl libaio1 build-essential python

# Install NodeJs
RUN curl -sL https://deb.nodesource.com/setup_6.x | bash - && \
    apt install -y nodejs && \
    apt clean

# Install Angular
RUN npm install -g @angular/cli

# Copy Application
COPY app /root/app

# Install Application
WORKDIR /root/app
RUN npm install && \
    ng build --env=prod

CMD ["node", "server.js"]
