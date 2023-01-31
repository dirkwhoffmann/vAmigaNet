/** @type {import('tailwindcss').Config} */
module.exports = {
	content: [
		'./src/**/*.{html,js,svelte,ts}',
		'./node_modules/flowbite-svelte/**/*.{html,js,svelte,ts}'
	],
	theme: {
		extend: {
			fontFamily: {
				josefin: ['"Josefin Sans"', 'sans-serif'],
				'sofia-semi': ['"Sofia Sans Semi Condensed"', 'sans-serif'],
				'sofia-extra': ['"Sofia Sans Extra Condensed"', 'sans-serif'],
				azeret: ['"Azeret Mono"', 'monospace']
			},
			backgroundImage: {
				splashscreen: "url('matrix1.jpg')"
			}
		}
	},
	plugins: [require('flowbite/plugin')],
  darkMode: 'class',
};
