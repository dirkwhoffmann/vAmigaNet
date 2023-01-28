<script lang="ts">
    export let css_class:string;
    export let free_positioning:boolean;
    export let x: number=0;
    export let y: number=200;
    let client_width: number;
    let client_height: number;
    let drag_start:boolean = false;

    let start_x:number=0;
    let start_y:number=0;
</script>
    
<svelte:window 
    on:mousemove={(e)=>{
        if(drag_start)
        {
            x= x-(start_x-e.clientX);
            y= y-(start_y-e.clientY);
            start_x=e.clientX;
            start_y=e.clientY;
        }
    } }
    on:mouseup={(e)=>{
        drag_start=false;
    }}
/>
    
<div class={css_class}
    bind:clientWidth={client_width} bind:clientHeight={client_height} style={free_positioning? "left:"+x+"px; top:"+y+"px;":""}>
    <div class="cursor-move select-none" 
        on:mousedown={(e)=>{
                start_x = e.clientX; 
                start_y = e.clientY;
                drag_start=true; 
            }
        }>
        <slot name="title"></slot>
    </div>
    <slot name="body"></slot>

</div>
    
    
