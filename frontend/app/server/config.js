exports.Config = {
    application: {
        port: 8080
    },
    database: {
        url: 'mongodb://mongodb:27017/prod',
        collection: 'images'
    },
    index: {
        hash_image_url: 'http://nginx:16000/api/hash_url',
        search_radius_url: 'http://nginx:16000/api/search_radius',
        search_knearest_url: 'http://nginx:16000/api/search_knearest',
        default_radius: 10,
        default_k: 10
    }
};
