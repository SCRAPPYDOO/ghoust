��/ /   g h o u s t . c p p   :   D e f i n e s   t h e   e n t r y   p o i n t   f o r   t h e   c o n s o l e   a p p l i c a t i o n .  
 / /  
  
 # i n c l u d e   " s t d a f x . h "  
  
 # i n c l u d e   " A c t i o n M a n a g e r . h "  
 # i n c l u d e   " W i n d o w M a n a g e r . h "  
 # i n c l u d e   " O b j e c t M a n a g e r . h "  
  
 u s i n g   n a m e s p a c e   s t d ;  
  
 i n t   m a i n ( )  
 {  
 	// W i n d o w M a n a g e r *   w i n d o w M a n a g e r   =   n e w   W i n d o w M a n a g e r ( ) ;  
  
 	 / / M e m o r y R e a d e r *   m e m o r y R e a d e r   =   n e w   M e m o r y R e a d e r ( w i n d o w M a n a g e r - > g e t P r o c e s s I d ( ) ) ;  
 	 / / M e m o r y R e a d e r : : g e t I n s t a n c e ( ) ;  
  
 LogicManager::getInstance();
 	 //O b j e c t M a n a g e r : : g e t I n s t a n c e ( ) ;  
  
 	 // c t i o n M a n a g e r *   a c t i o n M a n a g e r   =   n e w   A c t i o n M a n a g e r ( w i n d o w M a n a g e r - > g e t W i n d o w H a n d l e r ( ) ) ;  
  
 	 / * f o r   ( i n t   i   =   0 ;   i   <   2 0 0 ;   i + + )   {  
 	 	 a c t i o n M a n a g e r - > s t a r t A c t i o n ( A c t i o n : : M O V E _ L E F T ) ;  
 	 	 S l e e p ( 1 0 0 ) ;  
 	 	 a c t i o n M a n a g e r - > s t o p A c t i o n ( A c t i o n : : M O V E _ L E F T ) ;  
 	 	 S l e e p ( 1 0 0 0 0 ) ;  
 	 } * /  
  
 	 g e t c h a r ( ) ;  
 	 r e t u r n   0 ;  
  
 } 
