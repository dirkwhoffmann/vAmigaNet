/** @type {import('tailwindcss').Config} */
module.exports = {
	content: ['./src/**/*.{html,js,svelte,ts}'],
	theme: {
		extend: {
			fontFamily: {
				josefin: ['"Josefin Sans"', 'sans-serif'],
				'sofia-semi': ['"Sofia Sans Semi Condensed"', 'sans-serif'],
				'sofia-extra': ['"Sofia Sans Extra Condensed"', 'sans-serif'],
				azeret: ['"Azeret Mono"', 'monospace']
			},
			backgroundImage: {
				splashscreen: "url('matrix.jpg')"
			},

			colors: {
				// rose
				// primary: { "50": "#fff1f2", "100": "#ffe4e6", "200": "#fecdd3", "300": "#fda4af", "400": "#fb7185", "500": "#f43f5e", "600": "#e11d48", "700": "#be123c", "800": "#9f1239", "900": "#881337" }
				// primary: {"50":"#fdf2f8","100":"#fce7f3","200":"#fbcfe8","300":"#f9a8d4","400":"#f472b6","500":"#ec4899","600":"#db2777","700":"#be185d","800":"#9d174d","900":"#831843"}
				// primary: {"50":"#fff7ed","100":"#ffedd5","200":"#fed7aa","300":"#fdba74","400":"#fb923c","500":"#f97316","600":"#ea580c","700":"#c2410c","800":"#9a3412","900":"#7c2d12"}
				// slate
				/*				
				primary: {
					50: '#f8fafc',
					100: '#f1f5f9',
					200: '#e2e8f0',
					300: '#cbd5e1',
					400: '#94a3b8',
					500: '#64748b',
					600: '#475569',
					700: '#334155',
					800: '#1e293b',
					900: '#0f172a'
				}
				*/
			}
		}
	},
	daisyui: {
		themes: [ 'light', 'dark', 'coffee', 'cupcake', 'forest', 'aqua', 'garden', 'pastel',
			{
				mytheme: {
					primary: '#6D80A6',
					secondary: '#2336c4',
					accent: '#ddd6fe',
					neutral: '#131620',
					'base-100': '#1f2937',
					info: '#95AEE4',
					success: '#67E9AA',
					warning: '#EEEE00',
					error: '#F14170'
				}
			}
		]
	},
	plugins: [require('@tailwindcss/typography'), require('daisyui')],
	darkMode: 'class'
};
