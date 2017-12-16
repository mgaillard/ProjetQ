# Import data
mongoimport --host mongodb --db prod --collection images --type json --file /root/init.json
# Update the index
curl http://nginx:16000/api/update