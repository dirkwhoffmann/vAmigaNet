import { sveltekit } from '@sveltejs/kit/vite';
import type { UserConfig } from 'vite';
//import basicSsl from '@vitejs/plugin-basic-ssl'
import fs from 'fs';

const config: UserConfig = {
	plugins: [
		{
			name: 'configure-response-headers',
			configureServer: server => {
			  server.middlewares.use((_req, res, next) => {
				//these two headers are added by the serviceWorker.js so we do not need them to add here 
				//res.setHeader('Cross-Origin-Embedder-Policy', 'require-corp');
				//res.setHeader('Cross-Origin-Opener-Policy', 'same-origin');
				next();
			  });
			}
		},
		/*basicSsl(),*/sveltekit()],
	server: {
		https: {
		  key: fs.readFileSync('localhost-key.pem'),
		  cert: fs.readFileSync('localhost.pem'),
		},
	},




	test: {
		include: ['src/**/*.{test,spec}.{js,ts}']
	}
};

export default config;
