<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
     
     
   <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>	
     
     
          
	
	<xsl:template match="ferda_box">
				
				
				<element_attributes>
				
					<!-- vypise atributy-->
					<xsl:for-each select="@*">
						
						<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:choose>
							<xsl:when test="name()='box_type'">
								<xsl:text>Typ krabičky</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='user_name'">
								<xsl:text>Uživatelský název krabičky</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='user_hint'">
								<xsl:text>Poznámka</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:choose>
							<xsl:when test="name()='box_type'">
								<xsl:text>Box type</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='user_name'">
								<xsl:text>User name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='user_hint'">
								<xsl:text>User hint</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->
						
					
					
					
					
					
					
						<attribute name="{name()}" value="{.}" label="{$label}" />
					</xsl:for-each>
					
					<!--vypise properties-->
					<xsl:for-each select="febox_property">
						<attribute name="{@name}" value="{@value}" />
					</xsl:for-each>
					
				</element_attributes>
	</xsl:template>

	
	
    
</xsl:stylesheet>
