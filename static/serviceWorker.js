// install event
self.addEventListener('install', evt => {
    console.log('service worker installed');
    self.skipWaiting();
});

// activate event
self.addEventListener('activate', evt => {
    console.log('service worker activated');
});

self.addEventListener('fetch', function(event){
    event.respondWith(async function () {
        // console.log('serviceWorker: requested url '+event.request.url);
        let sw_request=event.request;

        var networkResponse = await fetch(sw_request, {cache: "no-cache"});
        event.waitUntil(
          async function () 
          {
            try {
              if(networkResponse.status == 200)
              {
                // console.log(`serviceWorker: status=200 for fetched resource: ${event.request.url}`)
              }
              else
              {
                // console.error(`serviceWorker: status=${networkResponse.status} for fetched resource: ${event.request.url}`)
              }
            }
            catch(e) { console.error(`exception during fetch ${e}`); }
          }()
        );   

        const newHeaders = new Headers(networkResponse.headers);
        newHeaders.set("Cross-Origin-Embedder-Policy", "require-corp");
        newHeaders.set("Cross-Origin-Opener-Policy", "same-origin");

        const moddedResponse = new Response(networkResponse.body, {
          status: networkResponse.status,
          statusText: networkResponse.statusText,
          headers: newHeaders,
        });
        return moddedResponse;
    
    }());
  });