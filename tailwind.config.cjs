/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ['./src/**/*.{html,js,svelte,ts}'],
  theme: {
    extend: {
      fontFamily: {
        'arimo': ['Arimo', 'sans-serif'],
        'josefin': ['Josefin Sans', 'sans-serif'],
        'rubik': ['Rubik Bubbles', 'cursive'],
      },
    },
  },
  plugins: [],
}
