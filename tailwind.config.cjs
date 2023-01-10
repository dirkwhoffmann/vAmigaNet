/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ['./src/**/*.{html,js,svelte,ts}'],
  theme: {
    extend: {
      fontFamily: {
        'josefin': ['Josefin Sans', 'sans-serif'],
        'sofia-semi': ['Sofia Sans Semi Condensed', 'sans-serif'],
        'sofia-extra': ['Sofia Sans Extra Condensed', 'sans-serif'],
      },
      backgroundImage: {
        'splashscreen': "url('background.jpg')",
      }    
    },
  },
  plugins: [],
}
