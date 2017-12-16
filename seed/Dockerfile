FROM mongo

# Install curl to update the index
RUN apt-get update && \
    apt-get install -y curl && \
    apt-get clean 

COPY seed.sh /root/seed.sh

COPY init.json /root/init.json

CMD ["bash", "/root/seed.sh"]