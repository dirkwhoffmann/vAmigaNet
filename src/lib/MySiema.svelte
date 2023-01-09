<script>
  import Siema from 'siema';
  import { onMount } from 'svelte';
  
  let slider, prev, next, radioSlider
  let select = 0

  onMount(() => {
      slider = new Siema({
              selector: '.siema',
              duration: 400,
              easing: 'ease-in-out',
              perPage: 4,
              startIndex: 0,
              draggable: true,
              multipleDrag: true,
              threshold: 20,
              loop: false,
              rtl: false,
              onInit: () => {},
              onChange: () => {},
          }); //end Siema constructor
      prev = () => {
          slider.prev()
          if (select > 0) {
              select--
          }
      }
      next = () => {
          slider.next()
          if (select >= 0) {
              select++
          }
      }
  }) //end onMount
const images = [
  {
    url: "https://res.cloudinary.com/beswift/image/upload/v1650391490/photo-1644241687200-eadaf7601290_xcz2kh.jpg",
    description: "image1",
  },
  {
    url: "https://res.cloudinary.com/beswift/image/upload/v1650391337/photo-1647067867267-e01d98462f3c_ugtnwe.jpg",
    description: "image2",
  },
  {
    url: "https://res.cloudinary.com/beswift/image/upload/v1650391131/photo-1648800475313-2bb7fbec8701_ae60yw.jpg",
    description: "image3",
  },
  {
    url: "https://res.cloudinary.com/beswift/image/upload/v1650390102/photo-1649894222226-056a1a79d9fb_xlv73h.jpg",
    description: "image4",
  },
  {
    url: "https://res.cloudinary.com/beswift/image/upload/v1650389425/photo-1649894221695-45abb718a190_sgjhwd.jpg",
    description: "image5",
  },
];
</script>
<main>
  <div class="siema">
  {#each images as src, imageIndex (src)}
    <div class="slider">
        <img src={src.url} alt={src.description} width={1000} height={600} />
    </div>
  {/each}
  </div>
</main>
<button on:click={prev}>
  prev
</button>
<button on:click={next}>
  next
</button>